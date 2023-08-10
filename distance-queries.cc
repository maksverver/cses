// Distance Queries
// https://cses.fi/problemset/task/1135
//
// The idea is that if we arbitrarily pick vertex 1 as the root, then the
// distance between v and w can be calculated by first finding the lowest common
// ancestor u. Then the shortest path between v-w must go through u, and we can
// calculate it as (depth[v] - depth[u]) + (depth[w] - depth[u]) =
// depth[v] + depth[w] - 2*depth[u].
//
//     1          1         |
//     |          |         |
//     v=u        u         |
//     |         / \        |
//     w        v   w       |
//
// See also company-queries-II.cc. This solution uses the same LCA computation.

#include <bits/stdc++.h>

using namespace std;

static vector<vector<int>> adj;
static vector<vector<int>> ancestors;
static vector<int> depth;

void Dfs1(int v, int parent) {
  depth[v] = depth[parent] + 1;
  ancestors[0][v] = parent;
  for (int w : adj[v]) if (w != parent) Dfs1(w, v);
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
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

  depth = vector<int>(N + 1);

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

  auto distance = [&](int v, int w)  {
    int u = lowest_common_ancestor(v, w);
    return depth[v] + depth[w] - depth[u] * 2;
  };

  for (int q = 0; q < Q; ++q) {
    int v = 0, w = 0;
    cin >> v >> w;
    cout << distance(v, w) << '\n';
  }
}
