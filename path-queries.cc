// Subtree Queries
// https://cses.fi/problemset/task/1137/
//
// Basically the complement to subtree-queries.cc.
//
// We start with an pre-order traversal to map each subtree to a contiguous
// subarray. Then we create a LazySegmentTree which contains for each vertex v
// the sum of values from `v` to the root. Adding `x` to the value at node
// `v` is then the same as adding `x` to all elements in the range matching the
// subtree of `v`.
//
// Complexity: O((N + Q) log N) time, O(N) space.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

template<class V, class C>
class LazySegmentTree {
public:
  // Initialize an empty segment tree of given size.
  LazySegmentTree(int size, V zero, C combine)
      : size(size), layers(CountLayers(size)),
        data(((1 << layers) - 1), zero),
        mutations(((1 << layers) - 1), zero),
        zero(std::move(zero)), combine(std::move(combine)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> LazySegmentTree(const std::vector<U> &v, V z, C c)
      : LazySegmentTree(v.size(), std::move(z), std::move(c)) {
    int k = (1 << (layers - 1)) - 1;
    for (int i = 0; i < v.size(); ++i) data[k + i] = v[i];
    for (int i = k - 1; i >= 0; --i) data[i] = combine(data[Child(i)], data[Child(i) + 1]);
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
      data[idx] += value * (min(j, end) - max(i, start));
      int mid = start + ((end - start) >> 1);
      if (i < mid) UpdateRange(i, j, Child(idx) + 0, start, mid, value);
      if (j > mid) UpdateRange(i, j, Child(idx) + 1, mid, end, value);
    }
  }

  int size;
  int layers;
  mutable vector<V> data;
  mutable vector<V> mutations;
  V zero;
  C combine;
};

vector<vector<int>> adj;
vector<int> begin;
vector<int> end;

static void Dfs(int v, int par, int &id) {
  begin[v] = id++;
  for (int w : adj[v]) if (w != par) Dfs(w, v, id);
  end[v] = id;
}

void Solve() {
  // Read input.
  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (int &a : A) cin >> a;
  adj = vector<vector<int>>(N);
  REP(_, N - 1) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  // Pre-order traversal to calculate begin/end indices.
  int id = 0;
  begin = vector<int>(N);
  end = vector<int>(N);
  Dfs(0, -1, id);
  assert(id == N);

  // Initialze segment tree so that element at index `begin[v]` contains the
  // sum of A from `v` to `0` (the root).
  LazySegmentTree tree(N, int64_t{0}, [](int64_t x, int64_t y){ return x + y; });
  REP(i, N) tree.AddRange(begin[i], end[i], A[i]);

  // Process queries.
  REP(_, Q) {
    int type = 0, v = 0;
    cin >> type >> v;
    --v;
    if (type == 1) {
      int x = 0;
      cin >> x;
      tree.AddRange(begin[v], end[v], x - A[v]);
      A[v] = x;
    } else {
      assert(type == 2);
      cout << tree.Get(begin[v]) << '\n';
    }
  }
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  Solve();
}
