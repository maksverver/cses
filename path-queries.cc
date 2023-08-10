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

#include "lazy-segment-tree.h"

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

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
