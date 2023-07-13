// Polynomial Queries
// https://cses.fi/problemset/task/1736
//
// Solution: Lazy Segment Tree modified to add increasing ranges instead
// of constant values.
//
// Instead of an update being a single integer value, it consists of a
// start s and an increment i implying that at this node, the sequence
// [s, s+i, s+2*i, s+3*i, s+4*i, ...] needs to be added.

#include <bits/stdc++.h>

using namespace std;

class LazySegmentTree {
public:
  using V = int64_t;

  // Initialize an empty segment tree of given size.
  LazySegmentTree(int size)
      : size(size), layers(CountLayers(size)),
        data(((1 << layers) - 1)),
        mutations(((1 << layers) - 1)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> LazySegmentTree(const std::vector<U> &v)
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
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : 0;
  }

  // Add `value` to all elements in range i..j (exclusive), or does nothing if i >= j.
  void AddRange(int i, int j) {
    assert(0 <= i && j <= size);
    if (i < j) UpdateRange(i, j, 0, 0, 1 << (layers - 1));
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

  // Returns the sum of (start + increment*i) for 0 ≤ i < length.
  static int64_t Sum(int start, int increment, int length) {
    // Integer overflow?
    return (int64_t) start * length + (int64_t) length * (length - 1) / 2 * increment;
  }

  void ClearUpdate(int idx, int width) const {
    if (mutations[idx].second == 0) return;
    auto [start, increment] = mutations[idx];
    data[idx] += Sum(start, increment, width);
    if (width > 1) {
      mutations[Child(idx) + 0].first += start;
      mutations[Child(idx) + 0].second += increment;
      assert(width % 2 == 0);
      mutations[Child(idx) + 1].first += start + increment * (width / 2);
      mutations[Child(idx) + 1].second += increment;
    }
    mutations[idx] = {0, 0};
  }

  V GetRange(int i, int j, int idx, int start, int end) const {
    ClearUpdate(idx, end - start);
    if (i <= start && j >= end) return data[idx];
    int mid = start + ((end - start) >> 1);
    V result = 0;
    if (i < mid) result += GetRange(i, j, Child(idx) + 0, start, mid);
    if (j > mid) result += GetRange(i, j, Child(idx) + 1, mid, end);
    return result;
  }

  void UpdateRange(int i, int j, int idx, int start, int end) {
    if (i <= start && j >= end) {
      mutations[idx].first += start - i + 1;
      mutations[idx].second += 1;
    } else {
      data[idx] += Sum(max(start - i + 1, 1), 1, min(j, end) - max(i, start));
      int mid = start + ((end - start) >> 1);
      if (i < mid) UpdateRange(i, j, Child(idx) + 0, start, mid);
      if (j > mid) UpdateRange(i, j, Child(idx) + 1, mid, end);
    }
  }

  int size;
  int layers;
  mutable vector<V> data;
  mutable vector<pair<int, int>> mutations;  // start, increment
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &a : A) cin >> a;
  LazySegmentTree tree(A);

  while (Q--) {
    int type = 0, a = 0, b = 0;;
    cin >> type >> a >> b;
    --a;
    if (type == 1) {
      tree.AddRange(a, b);
    } else {
      assert(type == 2);
      cout << tree.GetRange(a, b) << '\n';
    }
  }
}
