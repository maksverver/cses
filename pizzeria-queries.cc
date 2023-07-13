// Pizzeria Queries
// https://cses.fi/problemset/task/2206
//
// Solution:
//
// Let A[i] be the price in building i. Then the minimum cost at building j is
// the minimum of P[i] - i + j for 0 ≤ i ≤ j and P[i] + i - j for j ≤ i < N.
//
// We can store the values of `A[i] - i` in one segment tree, and the values of
// `A[i] + i` in another segment tree, and then we can calculate the cost in
// O(log N) time, for an O(N + Q log N) time solution.

#include <bits/stdc++.h>
#include <limits>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<typename V, typename C>
class SegmentTree {
public:
  SegmentTree(int size, V zero, C combine)
      : size(size), layers(CountLayers(size)), data(((1 << layers) - 1), zero),
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
  vector<V> data;
  V zero;
  C combine;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<int> V1(N);
  vector<int> V2(N);
  REP(i, N) V1[i] = A[i] - i;
  REP(i, N) V2[i] = A[i] + i;

  auto min = [](int a, int b) { return std::min(a, b); };
  SegmentTree<int, decltype(min)> tree1(V1, std::numeric_limits<int>::min(), min);
  SegmentTree<int, decltype(min)> tree2(V2, std::numeric_limits<int>::min(), min);

  REP(q, Q) {
    int type = 0, i = 0;
    cin >> type >> i;
    --i;
    if (type == 1) {
      int x = 0;
      cin >> x;
      tree1.Set(i, x - i);
      tree2.Set(i, x + i);
    } else {
      assert(type == 2);
      cout << min(tree1.GetRange(0, i + 1) + i, tree2.GetRange(i, N) - i) << '\n';
    }
  }
}
