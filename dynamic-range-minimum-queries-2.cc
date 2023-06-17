// Dynamic Range Minimum Queries
// https://cses.fi/problemset/task/1649
//
// Solution: ad-hoc segment tree

#include <bits/stdc++.h>

using namespace std;

template<typename V, typename C>
class SegmentTree {
public:
  SegmentTree(int size, V default_value, C combine)
      : size(size), layers(CountLayers(size)), data(((1 << layers) - 1), default_value),
        default_value(default_value), combine(combine) {}

  void Set(int i, V value) {
    assert(0 <= i && i < size);
    i = (1 << (layers - 1)) - 1 + i;
    data[i] = value;
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
  // or default_value if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : default_value;
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
  V default_value;
  C combine;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  auto min = [](int64_t a, int64_t b) { return a < b ? a : b; };
  int64_t max_value = std::numeric_limits<int64_t>::max();
  SegmentTree<int64_t, decltype(min)> tree(N, max_value, min);

  for (int i = 0; i < N; ++i) {
    int x = 0;
    cin >> x;
    tree.Set(i, x);
  }

  while (Q--) {
    int t = 0;
    cin >> t;
    if (t == 1) {
      int i = 0, x = 0;
      cin >> i >> x;
      --i;
      tree.Set(i, x);
    }
    if (t == 2) {
      size_t i = 0, j = 0;
      cin >> i >> j;
      --i;
      assert(i < j && j <= N);

      cout << tree.GetRange(i, j) << '\n';
    }
  }
}
