// Counting Paths
// https://cses.fi/problemset/task/1136
//
// Solution:
//
// Create a tree rooted at an arbitrary vertex (e.g. 1). Consider the path v-w.
// If v=w then the path starts and ends at v. Otherwise, let u=LCA(v, w). Then
// if u=v the path goes up from w to v. Otherwise, if u=w then the path goes up
// from v to w. Otherwise, the path goes up from v to u, then back down to w.
// In the last case, we can split the path into two paths: one from v up to u,
// and one from w up to the child of u that leads to w. This doesn't change the
// count of paths per node!
//
// So without loss of generality, we can assume all paths go from some deep
// vertex v up to some higher vertex w that lies on the path from v to the root.
// If we count for each vertex how many paths start and end at that vertex, we
// can recursively solve the problem.
//
// See also distance-queries.cc. This solution uses the same tree construction
// and LCA computation.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

static vector<vector<int>> adj;
static vector<vector<int>> ancestors;
static vector<int> depth;
static vector<int> paths_beginning;
static vector<int> paths_ending;
static vector<int> paths_count;

void Dfs1(int v, int parent) {
  depth[v] = depth[parent] + 1;
  ancestors[0][v] = parent;
  for (int w : adj[v]) if (w != parent) Dfs1(w, v);
}

int Dfs2(int v, int parent) {
  int n = paths_beginning[v];
  for (int w : adj[v]) if (w != parent) n += Dfs2(w, v);
  paths_count[v] = n;
  n -= paths_ending[v];
  assert(n >= 0);
  return n;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  adj = vector<vector<int>>(N + 1);
  for (int e = 0; e < N - 1; ++e) {
    int v = 0, w = 0;
    cin >> v >> w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  int layers = 1;
  while ((1 << (layers - 1)) < N) ++layers;
  ancestors = vector<vector<int>>(layers, vector<int>(N + 1));

  depth           = vector<int>(N + 1);
  paths_beginning = vector<int>(N + 1);;
  paths_ending    = vector<int>(N + 1);;
  paths_count     = vector<int>(N + 1);;

  // Intialize `depth[v]` and `ancestors[0][v]` for all 1 ≤ v ≤ N.
  Dfs1(1, 0);

  // Calculate `ancestors[i][v]` for all 1 ≤ i < layers, 1 ≤ v ≤ N.
  for (int l = 1; l < layers; ++l) {
    for (int i = 1; i <= N; ++i) {
      ancestors[l][i] = ancestors[l - 1][ancestors[l - 1][i]];
    }
  }

  auto nth_ancestor = [&](int v, int n) {
    for (int l = 0; v > 0 && n > 0; ++l, n >>= 1) {
      if (n & 1) v = ancestors[l][v];
    }
    return v;
  };

  auto lowest_common_ancestor = [&](int v, int w) {
    if (depth[v] > depth[w]) v = nth_ancestor(v, depth[v] - depth[w]);
    if (depth[w] > depth[v]) w = nth_ancestor(w, depth[w] - depth[v]);

    if (v == w) return v; // v was an ancestor w, or vice versa.

    // v and w have a different lowest ancestor.
    for (int l = layers - 1; l >= 0 && v != w; --l) {
      if (ancestors[l][v] != ancestors[l][w]) {
        v = ancestors[l][v];
        w = ancestors[l][w];
      }
    }
    assert(v != w && ancestors[0][v] == ancestors[0][w]);
    return ancestors[0][v];
  };

  for (int m = 0; m < M; ++m) {
    int v = 0, w = 0;
    cin >> v >> w;
    if (v == w) {
      ++paths_beginning[v];
      ++paths_ending[v];
    } else {
      int u = lowest_common_ancestor(v, w);
      if (u == v) {
        ++paths_beginning[w];
        ++paths_ending[v];
      } else if (u == w) {
        ++paths_beginning[v];
        ++paths_ending[w];
      } else {
        ++paths_beginning[v];
        ++paths_ending[u];

        ++paths_beginning[w];
        int x = nth_ancestor(w, depth[w] - depth[u] - 1);
        assert(ancestors[0][x] == u);
        ++paths_ending[x];
      }
    }
  }

  int paths_remaining = Dfs2(1, 0);
  std::cerr << paths_remaining << '\n';
  assert(paths_remaining == 0);

  for (int v = 1; v <= N; ++v) {
    if (v > 1) cout << ' ';
    cout << paths_count[v];
  }
  cout << '\n';
}
