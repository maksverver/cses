#include <bits/stdc++.h>

using namespace std;

template<typename V, typename C>
class SegmentTree {
public:
  SegmentTree(int height, int width, V zero, C combine)
    : height(height), width(width),
      layers1(CountLayers(height)), layers2(CountLayers(width)),
      data(((1 << layers1) - 1), vector<V>((1 << layers2) - 1, zero)),
      zero(std::move(zero)), combine(std::move(combine)) {}

  // Initialize a segment tree from a vector of same-length vectors.
  template<class U> SegmentTree(const std::vector<std::vector<U>> &v, V zero, C combine)
    : SegmentTree(v.size(), v[0].size(), std::move(zero), std::move(combine)) {
    int k1 = (1 << (layers1 - 1)) - 1;
    int k2 = (1 << (layers2 - 1)) - 1;
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        data[k1 + r][k2 + c] = v[r][c];
      }
      for (int j = k2 - 1; j >= 0; --j) {
        data[k1 + r][j] = combine(data[k1 + r][Child(j)], data[k1 + r][Child(j) + 1]);
      }
    }
    for (int i = k1 - 1; i >= 0; --i) {
      for (int j = 0; j < (1 << layers2) - 1; ++j) {
        data[i][j] = combine(data[Child(i)][j], data[Child(i) + 1][j]);
      }
    }
  }

  void Set(int r, int c, V value) {
    assert(0 <= r && r < height);
    assert(0 <= c && c < width);
    int i = (1 << (layers1 - 1)) - 1 + r;
    int j = (1 << (layers2 - 1)) - 1 + c;
    for (;;) {
      data[i][j] = value;
      for (int k = i; k != 0; ) {
        k = Parent(k);
        data[k][j] = combine(data[Child(k)][j], data[Child(k) + 1][j]);
      }
      if (j == 0) break;
      j = Parent(j);
      value = combine(data[i][Child(j)], data[i][Child(j) + 1]);
    }
  }

  V Get(int r, int c) const {
    assert(0 <= r && r < height);
    assert(0 <= c && c < width);
    return data[(1 << (layers1 - 1)) - 1 + r][(1 << (layers2 - 1)) - 1 + c];
  }

  // Returns the combined value for (r, c) where r1 <= r < r2, c1 <= c < c2,
  // or zero if r1 >= r2 or c1 >= c2.
  V GetRange(int r1, int c1, int r2, int c2) const {
    assert(0 <= r1 && r2 <= height);
    assert(0 <= c1 && c2 <= width);
    return r1 < r2 && c1 < c2 ? GetRange1(r1, r2, c1, c2, 0, 0, 1 << (layers1 - 1)) : zero;
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

  V GetRange1(int r1, int r2, int c1, int c2, int idx1, int start, int end) const {
    if (r1 <= start && r2 >= end) {
      return GetRange2(idx1, c1, c2, 0, 0, 1 << (layers2 - 1));
    }
    int mid = start + ((end - start) >> 1);
    if (r2 <= mid) {
      return GetRange1(r1, r2, c1, c2, Child(idx1), start, mid);
    }
    if (r1 >= mid) {
      return GetRange1(r1, r2, c1, c2, Child(idx1) + 1, mid, end);
    }
    return combine(
      GetRange1(r1, r2, c1, c2, Child(idx1), start, mid),
      GetRange1(r1, r2, c1, c2, Child(idx1) + 1, mid, end));
  }

  V GetRange2(int idx1, int c1, int c2, int idx2, int start, int end) const {
    if (c1 <= start && c2 >= end) {
      return data[idx1][idx2];
    }
    int mid = start + ((end - start) >> 1);
    if (c2 <= mid) {
      return GetRange2(idx1, c1, c2, Child(idx2), start, mid);
    }
    if (c1 >= mid) {
      return GetRange2(idx1, c1, c2, Child(idx2) + 1, mid, end);
    }
    return combine(
      GetRange2(idx1, c1, c2, Child(idx2), start, mid),
      GetRange2(idx1, c1, c2, Child(idx2) + 1, mid, end));
  }

  int height, width;
  int layers1, layers2;
  vector<vector<V>> data;  // layers1 x layers2
  V zero;
  C combine;
};


int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<vector<int>> A(N, vector<int>(N));
  for (int r = 0; r < N; ++r) {
    string s;
    cin >> s;
    assert(s.size() == N);
    for (int c = 0; c < N; ++c) {
      A[r][c] = s[c] == '*';
    }
  }

  auto sum = [](int a, int b) { return a + b; };
  SegmentTree tree(A, 0, sum);

  while (Q--) {
    int type = 0;
    cin >> type;
    if (type == 1) {
      int r = 0, c = 0;
      cin >> r >> c;
      --r, --c;
      tree.Set(r, c, tree.Get(r, c) ^ 1);
    } else {
      assert(type == 2);
      int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
      cin >> r1 >> c1 >> r2 >> c2;
      --r1, --c1;
      cout << tree.GetRange(r1, c1, r2, c2) << '\n';
    }
  }
}
