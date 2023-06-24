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

vector<vector<int>> next;
vector<vector<int>> prev;

// Uses Hierholzer's algorithm to find a Eulerian cycle in a directed graph
// in O(V + E) time.
//
// A Eularian cycle exists if and only if:
//
//  1. All vertices in the graph have equal indegree and outdegree.
//  2. The edge set of the graph is connected.
//
// If these conditions are fulfilled, this function returns a deque of integers
// whose size is equal to the number of edges: the vertices in the cycle in
// order (with an edge from the last vertex to the first to complete the cycle).
// Otherwise, it returns an empty deque.
deque<int> FindEulerianCycle() {
  deque<int> cycle;

  // Check condition 1: all vertices have equal indegree and outdegree.
  size_t edge_count = 0;
  for (int v = 0; v < next.size(); ++v) {
    if (next[v].size() != prev[v].size()) return cycle;
    edge_count += next[v].size();
  }

  auto extend = [&](int v) {
    while (!next[v].empty()) {
      int w = next[v].back();
      next[v].pop_back();
      cycle.push_back(w);
      v = w;
    }
  };

  // Find an initial cycle.
  int v = 0;
  while (v < next.size() && next[v].empty()) ++v;
  if (v == next.size()) return cycle;
  extend(v);

  // Extend the cycle maximally.
  int skips = 0;
  while (skips < cycle.size()) {
    int v = cycle.back();
    cycle.pop_back();
    if (next[v].empty()) {
      cycle.push_front(v);
      ++skips;
    } else {
      cycle.push_back(v);
      extend(v);
      skips = 0;
    }
  }

  // Check condition 2: the edge set is connected.
  if (cycle.size() != edge_count) return {};

  return cycle;
}

void Solve() {
  int V = 0, E = 0;
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
  std::cerr << cycle.size() << '\n';
  if (cycle.empty()) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    assert(cycle.size() == E + 1);

    // Rotate so we start from 1 and end at N
    while (cycle.front() != 0 || cycle.back() != V - 1)  {
      int v = cycle.front();
      cycle.pop_front();
      cycle.push_back(v);
    }
    for (int i = 0; i < cycle.size(); ++i) {
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
