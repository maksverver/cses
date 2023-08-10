// Regular Segment Tree with an arbitrary data type and combining operation.
//
// Keep this in sync with codelib3/SegmentTree.cc.

#ifndef SEGMENT_TREE_H_INCLUDED
#define SEGMENT_TREE_H_INCLUDED

#include <cassert>
#include <utility>
#include <vector>

template<class V, class C>
class SegmentTree {
public:
  SegmentTree(int size, V zero, C combine)
      : size(size), layers(CountLayers(size)), data((1 << layers) - 1, zero),
        zero(std::move(zero)), combine(std::move(combine)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> SegmentTree(const std::vector<U> &v, V zero, C combine)
      : SegmentTree(v.size(), std::move(zero), std::move(combine)) {
    int k = (1 << (layers - 1)) - 1;
    for (int i = 0; i < v.size(); ++i) data[k + i] = v[i];
    for (int i = k - 1; i >= 0; --i) data[i] = combine(data[Child(i)], data[Child(i) + 1]);
  }

  void Set(int i, V value) {
    assert(0 <= i && i < size);
    i = (1 << (layers - 1)) - 1 + i;
    data[i] = std::move(value);
    while (i > 0) {
      i = Parent(i);
      data[i] = combine(data[Child(i)], data[Child(i) + 1]);
    }
  }

  V Get(int i) const {
    assert(0 <= i && i < size);
    return data[(1 << (layers - 1)) - 1 + i];
  }

  // Returns the combined value over the range i..j (exclusive),
  // or zero if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : zero;
  }

  // Returns the least index `j` such that value <= GetRange(0, j), or if there
  // is no such value, returns `size` + 1 instead.
  //
  // Assumes values of GetRange(0, j) are ordered according to `compare`
  // (std::greater<V>() for sum and maximum, std::less<V>() for minimum, etc.)
  template<class Compare>
  int LowerBound(const V &value, const Compare &compare) const {
    if (layers == 0) return compare(zero, value);  // size == 0
    if (compare(data[0], value)) return size + 1;  // value > GetRange(0, size)

    // Invariant: acc is the combined value from 0 to start (exclusive)
    V acc = zero;
    int idx = 0, start = 0, end = 1 << (layers - 1);
    while (end - start > 1) {
      int mid = start + ((end - start) >> 1);
      V tmp = combine(acc, data[Child(idx)]);
      if (compare(tmp, value)) {  // tmp < value
        acc = std::move(tmp);
        start = mid;
        idx = Child(idx) + 1;
      } else {  // tmp >= value
        end = mid;
        idx = Child(idx);
      }
    }
    assert(end - start == 1);
    assert(!compare(combine(acc, data[idx]), value));  // acc + data[idx] >= value
    return start + compare(acc, value);
  }

  // Returns the least index `j` such that value < GetRange(0, j), or if there
  // is no such value, returns `size` + 1 instead.
  //
  // Let i = LowerBound(v) and j = UpperBound(v), then GetRange(0, k) = v for
  // all i <= k < j, and (j - i) is the number of prefixes that have a combined
  // value of exactly `v`.
  //
  // Assumes values of GetRange(0, j) are ordered according to `compare`
  // (std::greater<V>() for sum and maximum, std::less<V>() for minimum, etc.)
  template<class Compare>
  int UpperBound(const V &value, const Compare &compare) const  {
    if (layers == 0) return !compare(value, zero);  // size == 0
    if (!compare(value, data[0])) return size + 1;  // value >= GetRange(0, size)

    // Invariant: acc is the combined value from 0 to start (exclusive)
    V acc = zero;
    int idx = 0, start = 0, end = 1 << (layers - 1);
    while (end - start > 1) {
      int mid = start + ((end - start) >> 1);
      V tmp = combine(acc, data[Child(idx)]);
      if (!compare(value, tmp)) {  // tmp <= value
        acc = std::move(tmp);
        start = mid;
        idx = Child(idx) + 1;
      } else {  // tmp > value
        end = mid;
        idx = Child(idx);
      }
    }
    assert(end - start == 1);
    assert(compare(value, combine(acc, data[idx])));  // acc + data[idx] > value
    return start + !compare(value, acc);
  }

private:
  static int Parent(int i) {
    return (i - 1) >> 1;
  }

  static int Child(int i) {
    return 2*i + 1;
  }

  static int CountLayers(int size) {
    int layers = size > 0;
    while (size > 1) {
      size = (size + 1) >> 1;
      ++layers;
    }
    return layers;
  }

  V GetRange(int i, int j, int idx, int start, int end) const {
    if (i <= start && j >= end) {
      return data[idx];
    }
    int mid = start + ((end - start) >> 1);
    if (j <= mid) {
      return GetRange(i, j, Child(idx), start, mid);
    }
    if (i >= mid) {
      return GetRange(i, j, Child(idx) + 1, mid, end);
    }
    return combine(
      GetRange(i, j, Child(idx), start, mid),
      GetRange(i, j, Child(idx) + 1, mid, end));
  }

  int size;
  int layers;
  std::vector<V> data;
  V zero;
  C combine;
};

#endif  // ndef SEGMENT_TREE_H_INCLUDED
