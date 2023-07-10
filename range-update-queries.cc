// Range Update Queries
// https://cses.fi/problemset/task/1651
//
// Problem:
//
// We are given an initial array and a list of queries, each of which either
// asks to print the value at a position, or to add a value to each element in a
// subarray.
//
// Solution:
//
// Use a lazy segment tree to store the contents of the array.

#include <bits/stdc++.h>

using namespace std;

template<typename V>
class LazySegmentTree {
public:
  // Initialize an empty segment tree of given size.
  LazySegmentTree(int size, V zero)
      : size(size), layers(CountLayers(size)),
        data(((1 << layers) - 1), zero),
        updates(((1 << layers) - 1), zero),
        zero(std::move(zero)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> LazySegmentTree(const std::vector<U> &v, V zero)
      : size(v.size()), layers(CountLayers(size)),
        data(((1 << layers) - 1), zero),
        updates(((1 << layers) - 1), zero),
        zero(std::move(zero)) {
    Init(v, 0, 0, 1 << (layers - 1));
  }

  // Returns the value at index i.
  V Get(int i) const {
    return GetRange(i, i + 1);
  }

  // Returns the sum of elements in range i..j (exclusive),
  // or zero if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : zero;
  }

  // Adds `value` at index i.
  void Update(int i, const V &value) {
    UpdateRange(i, i + 1, value);
  }

  // Add `value` to all elements in range i..j (exclusive),
  // or does nothing if i >= j.
  void UpdateRange(int i, int j, const V &value) {
    assert(0 <= i && j <= size);
    if (i < j) UpdateRange(i, j, 0, 0, 1 << (layers - 1), value);
  }

private:
  static int Parent(int i) { return (i - 1) >> 1; }
  static int Child(int i) { return 2*i + 1; }

  static int CountLayers(int size) {
    int layers = size > 0;
    while (size > 1) {
      size = (size + 1) >> 1;
      ++layers;
    }
    return layers;
  }

  template<class U> void Init(const vector<U> &v, int idx, int start, int end) {
    if (start >= v.size()) return;
    if (end - start == 1) {
      data[idx] = v[start];
    } else {
      int mid = start + ((end - start) >> 1);
      int c1 = Child(idx), c2 = c1 + 1;
      Init(v, c1, start, mid);
      Init(v, c2, mid, end);
      data[idx] = data[c1] + data[c2];
    }
  }

  void ClearUpdate(int idx, int width) const {
    if (updates[idx] == zero) return;
    data[idx] += updates[idx] * width;
    if (width > 1) {
      int c = Child(idx);
      if (c + 0 < data.size()) updates[c + 0] += updates[idx];
      if (c + 1 < data.size()) updates[c + 1] += updates[idx];
    }
    updates[idx] = zero;
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
      updates[idx] += value;
    } else {
      data[idx] += value * (min(j, end) - max(i, start));
      int mid = start + ((end - start) >> 1);
      if (i < mid) UpdateRange(i, j, Child(idx) + 0, start, mid, value);
      if (j > mid) UpdateRange(i, j, Child(idx) + 1, mid, end, value);
    }
  }

  int size;
  int layers;
  mutable vector<V> data;
  mutable vector<V> updates;
  V zero;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  LazySegmentTree<int64_t> tree(A, 0);
  while (Q--) {
    int type = 0;
    cin >> type;
    if (type == 1) {
      int i = 0, j = 0, v = 0;
      cin >> i >> j >> v;
      tree.UpdateRange(i - 1, j, v);
    } else {
      assert(type == 2);
      int i = 0;
      cin >> i;
      cout << tree.Get(i - 1) << '\n';
    }
  }
}
