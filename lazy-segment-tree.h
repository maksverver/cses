// LazySegmentTree. A segment tree of integers that supports range updates.

#ifndef LAZY_SEGMENT_TREE
#define LAZY_SEGMENT_TREE

#include <cassert>
#include <utility>
#include <vector>

template<class V>
class LazySegmentTree {
  static const V zero;

public:
  // Initialize an empty segment tree of given size.
  explicit LazySegmentTree(int size)
      : size(size), layers(CountLayers(size)),
        data(((1 << layers) - 1), zero),
        mutations(((1 << layers) - 1), zero) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> explicit LazySegmentTree(const std::vector<U> &v)
      : LazySegmentTree(v.size()) {
    int k = (1 << (layers - 1)) - 1;
    for (int i = 0; i < v.size(); ++i) data[k + i] = v[i];
    for (int i = k - 1; i >= 0; --i) data[i] = data[Child(i)] + data[Child(i) + 1];
  }

  // Returns the value at index i.
  V Get(int i) const {
    return GetRange(i, i + 1);
  }

  // Returns the sum of elements in range i..j (exclusive), or zero if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : zero;
  }

  // Adds `value` at index i.
  void Add(int i, const V &value) {
    AddRange(i, i + 1, value);
  }

  // Add `value` to all elements in range i..j (exclusive), or does nothing if i >= j.
  void AddRange(int i, int j, const V &value) {
    assert(0 <= i && j <= size);
    if (i < j) UpdateRange(i, j, 0, 0, 1 << (layers - 1), value);
  }

private:
  static int Parent(int i) { return (i - 1) >> 1; }  // unused
  static int Child(int i) { return 2*i + 1; }

  static int CountLayers(int size) {
    int layers = size > 0;
    while (size > 1) {
      size = (size + 1) >> 1;
      ++layers;
    }
    return layers;
  }

  void ClearUpdate(int idx, int width) const {
    if (mutations[idx] == zero) return;
    data[idx] += mutations[idx] * width;
    if (width > 1) {
      mutations[Child(idx) + 0] += mutations[idx];
      mutations[Child(idx) + 1] += mutations[idx];
    }
    mutations[idx] = zero;
  }

  V GetRange(int i, int j, int idx, int start, int end) const {
    ClearUpdate(idx, end - start);
    if (i <= start && j >= end) return data[idx];
    int mid = start + ((end - start) >> 1);
    V result = zero;
    if (i < mid) result += GetRange(i, j, Child(idx) + 0, start, mid);
    if (j > mid) result += GetRange(i, j, Child(idx) + 1, mid, end);
    return result;
  }

  void UpdateRange(int i, int j, int idx, int start, int end, const V &value) {
    if (i <= start && j >= end) {
      mutations[idx] += value;
    } else {
      data[idx] += value * (std::min(j, end) - std::max(i, start));
      int mid = start + ((end - start) >> 1);
      if (i < mid) UpdateRange(i, j, Child(idx) + 0, start, mid, value);
      if (j > mid) UpdateRange(i, j, Child(idx) + 1, mid, end, value);
    }
  }

  int size;
  int layers;
  mutable std::vector<V> data;
  mutable std::vector<V> mutations;
};

template<class V> const V LazySegmentTree<V>::zero = {};

#endif  // ndef LAZY_SEGMENT_TREE
