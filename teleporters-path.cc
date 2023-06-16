// Teleporters Path
// https://cses.fi/problemset/task/1693
//
// Problem:
//
// Find a Eulerian cycle in a directed graph (i.e., a cycle that
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
//
// See also mail-delivery.cc for the undirected version of this problem.

#include <bits/stdc++.h>

using namespace std;

namespace {

int V, E;
vector<vector<int>> next;
vector<vector<int>> prev;

deque<int> FindEulerianCycle() {
  deque<int> cycle;

  // A Eulerian cycle requires that all vertices have equal in- and outdegree.
  // This doesn't check that the graph is connected, which is also required,
  // but we'll detect that later.
  for (int v = 0; v < V; ++v) {
    if (next[v].size() != prev[v].size()) return cycle;
  }

  int skips = 0;
  cycle.push_back(0);
  while (skips < cycle.size()) {
    int v = cycle.front();
    cycle.pop_front();
    if (prev[v].empty()) {
      cycle.push_back(v);
      ++skips;
      continue;
    }
    skips = 0;
    cycle.push_front(v);
    while (!prev[v].empty()) {
      int u = prev[v].back();
      prev[v].pop_back();
      cycle.push_front(u);
      v = u;
    }
  }

  // Rotate the cycle so it starts and ends with 0.
  while (cycle.front() != 0 || cycle.back() != 0) {
    int v = cycle.front();
    cycle.pop_front();
    cycle.push_back(v);
  }

  return cycle;
}

void Solve() {
  cin >> V >> E;
  next.resize(V);
  prev.resize(V);
  for (int e = 0; e < E; ++e) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    next[v].push_back(w);
    prev[w].push_back(v);
  }

  // Add extra edge from last to first vertex, so we can treat it as a Eulerian
  // cycle problem.
  next[V - 1].push_back(0);
  prev[0].push_back(V - 1);

  deque<int> cycle = FindEulerianCycle();
  if (cycle.size() != E + 2) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (int i = 0; i < cycle.size() - 1; ++i) {
      if (i > 0) cout << ' ';
      cout << cycle[i] + 1;
    }
    cout << endl;
  }
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  Solve();
}
