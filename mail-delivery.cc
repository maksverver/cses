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
//
// See also teleporters-path.cc for the directed version of this problem.

#include <bits/stdc++.h>

using namespace std;

namespace {

struct Edge {
  int v, w;
};

// Uses Hierholzer's algorithm to find a Eulerian cycle in an undirected graph
// in O(V + E) time.
//
// V is an upperbound on the number of vertices (0 <= edge.v, edge.w < V).
//
// A Eularian cycle exists if and only if:
//
//  1. All vertices in the graph have even degree.
//  2. The edge set of the graph is connected.
//
// If these conditions are fulfilled, this function returns a deque of integers
// whose size is equal to the number of edges: the vertices in the cycle in
// order (with an edge from the last vertex to the first to complete the cycle).
// Otherwise, it returns an empty deque.
deque<int> FindEulerianCycle(int V, const vector<Edge> &edges) {
  deque<int> cycle;

  vector<char> edge_used(edges.size());
  vector<vector<size_t>> adj(V);

  for (size_t i = 0; i < edges.size(); ++i) {
    auto [v, w] = edges[i];
    adj[v].push_back(i);
    adj[w].push_back(i);
  }

  // Check condition 1: all vertices must have even degree. This guarantees that
  // extend() (defined below) will always find a full cycle that ends at the
  // vertex where it started.
  for (const auto &a : adj) {
    if (a.size() % 2 != 0) return {};
  }

  // Extracts an unused edge {v, w} and returns `w`, or returns -1 if `v` has no
  // unused successors left.
  auto successor = [&](int v) {
    while (!adj[v].empty() && edge_used[adj[v].back()]) adj[v].pop_back();
    if (adj[v].empty()) return -1;
    size_t i = adj[v].back();
    edge_used[i] = true;
    if (edges[i].v == v) return edges[i].w;
    if (edges[i].w == v) return edges[i].v;
    assert(false);
    return -1;
  };

  // Adds edges to the cycle starting from `v` until no successors are left.
  auto extend = [&](int v) {
    while ((v = successor(v)) != -1) {
      cycle.push_back(v);
    }
  };

  // Find an initial cycle.
  for (int v = 0; v < V; ++v) {
    int w = successor(v);
    if (w != -1) {
      cycle.push_back(w);
      extend(w);
      assert(cycle.back() == v);
      break;
    }
  }
  // Extend the cycle maximally.
  int skips = 0;
  while (skips < cycle.size()) {
    int v = cycle.back();
    cycle.pop_back();
    int w = successor(v);
    if (w == -1) {
      cycle.push_front(v);
      ++skips;
    } else {
      cycle.push_back(v);
      cycle.push_back(w);
      extend(w);
      assert(cycle.back() == v);
      skips = 0;
    }
  }

  // Check condition 2: edge set must be connected. If not, we end up with a
  // maximal cycle that is shorter than the number of edges.
  if (cycle.size() != edges.size()) return {};

  return cycle;
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  std::vector<Edge> edges(E);
  for (auto &[v, w] : edges) cin >> v >> w, --v, --w;

  deque<int> cycle = FindEulerianCycle(V, edges);
  if (auto it = std::find(cycle.begin(), cycle.end(), 0); it == cycle.end()) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    assert(cycle.size() == E);
    std::rotate(cycle.begin(), it, cycle.end());
    cout << 1;
    for (int i = 1; i < cycle.size(); ++i) {
      cout << ' ' << cycle[i] + 1;
    }
    cout << ' ' << 1 << endl;
  }
}
