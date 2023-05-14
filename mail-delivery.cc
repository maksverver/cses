// Mail Delivery
// https://cses.fi/problemset/task/1691
//
// Problem:
//
// Find a Eulerian cycle in an undirected graph (i.e., a cycle that
// visits each edge exactly once).
//
// Solution:
//
// Hierholzer's algorithm: follow unvisited edges to find a cycle from 1 to 1.
// Then, while there is a vertex `v` on the cycle that has unvisted edges, find
// a cycle from `v` to `v` by following unvisited edges, and insert it into the
// cycle.
//
// The overall algorithm is O(E) when implemented correctly.

#include <bits/stdc++.h>

using namespace std;

namespace {

struct Edge {
  int w;
  int edge_index;
};

int V, E;
vector<char> edge_used;
vector<vector<Edge>> adj;

int ExtractUnusedEdge(int v) {
  while (!adj[v].empty() && edge_used[adj[v].back().edge_index]) adj[v].pop_back();
  if (adj[v].empty()) return -1;
  auto [w, e] = adj[v].back();
  edge_used[e] = true;
  return w;
}

deque<int> FindEulerianCycle() {
  deque<int> cycle;

  // A Eulerian cycle requires that all vertices have even degree.
  // This doesn't check that the graph is connected, which is also required,
  // but we'll detect that later.
  for (const auto &edges : adj) {
    if (edges.size() % 2 != 0) return cycle;
  }

  int skips = 0;
  cycle.push_back(0);
  while (skips < cycle.size()) {
    int v = cycle.front();
    cycle.pop_front();
    int w = ExtractUnusedEdge(v);
    if (w == -1) {
      cycle.push_back(v);
      ++skips;
      continue;
    }
    skips = 0;
    cycle.push_front(v);
    do {
      cycle.push_front(w);
      w = ExtractUnusedEdge(w);
    } while (w != -1);
  }

  // Rotate the cycle so it starts and ends with 0.
  while (cycle.front() != 0 || cycle.back() != 0) {
    int v = cycle.front();
    cycle.pop_front();
    cycle.push_back(v);
  }

  return cycle;
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  cin >> V >> E;
  edge_used.assign(E, false);
  adj.resize(V);
  for (int e = 0; e < E; ++e) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back({w, e});
    adj[w].push_back({v, e});
  }

  deque<int> cycle = FindEulerianCycle();
  if (cycle.size() != E + 1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int i = 0; i < cycle.size(); ++i) {
      if (i > 0) cout << ' ';
      cout << cycle[i] + 1;
    }
    cout << endl;
  }
}
