// Company Queries II
// https://cses.fi/problemset/task/1688
//
// Lowest Common Ancestor (LCA)
//
// See also company-queries-I.cc, which calculates nth_ancestor() the same way.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  int layers = 1;
  while ((1 << (layers - 1)) < N) ++layers;

  // ancestors[l][i] is the 2^l-th ancestor of i.
  vector<vector<int>> ancestors(layers, vector<int>(N + 1));
  vector<int> depth(N + 1);
  for (int i = 2; i <= N; ++i) {
    int parent = 0;
    cin >> parent;
    ancestors[0][i] = parent;
    // This works because the input guarantees that parent < i.
    depth[i] = depth[parent] + 1;
  }
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

  while (Q-- > 0) {
    int v = 0, w = 0;
    cin >> v >> w;
    cout << lowest_common_ancestor(v, w) << '\n';
  }
}
