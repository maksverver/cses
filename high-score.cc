// High Score
// https://cses.fi/problemset/task/1673
//
// Problem:
//
// Find the longest path in a graph, allowing vertices to be revisited.
//
// Solution:
//
// Variant of Bellman-Ford, but instead of searching for the shortest path, we
// will search for the longest.
//
// First, we do two breadth-first-searches to identify the vertices reachable
// from the start and from which the finish can be reached, and delete the
// others, since they cannot be part of a solution. (This is not just an
// optimization, but required for correctness!)
//
// Then we will run Bellman-Ford: first we relax all edges (V - 1) times, which
// is guaranteed to find all non-cyclic maximum score paths, since such paths
// consist of at most V - 1 edges. Then we can check if we could still relax
// any edge, which is true iff. there is a positive-score cycle in the graph,
// and since we have removed vertices that do not lie on a path between start
// and finish, the existence of any positive-weight cycle is sufficient to
// conclude we can reach the finish with an arbitrarily-high score.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Edge {
  int v, w, c;
};

static int64_t Solve() {
  int V = 0, E = 0;
  cin >> V >> E;
  vector<Edge> edges(E);
  for (auto &[v, w, c] : edges) {
    cin >> v >> w >> c;
    --v, --w;
  }

  // Breadth-first search for vertices reachable from start.
  vector<char> reach_start(V, false);
  {
    vector<vector<int>> adj(V);
    for (auto [v, w, c] : edges) adj[v].push_back(w);
    deque<int> todo;
    reach_start[0] = true;
    todo.push_back(0);
    while (!todo.empty()) {
      int v = todo.front();
      todo.pop_front();
      for (int w : adj[v]) if (!reach_start[w]) {
        reach_start[w] = true;
        todo.push_back(w);
      }
    }
  }

  // Breadth-first search using reversed edges to find vertices
  // from which finish is reachable.
  vector<char> reach_finish(V, false);
  {
    vector<vector<int>> adj(V);
    for (auto [v, w, c] : edges) adj[w].push_back(v);
    deque<int> todo;
    reach_finish[V - 1] = true;
    todo.push_back(V - 1);
    while (!todo.empty()) {
      int v = todo.front();
      todo.pop_front();
      for (int w : adj[v]) if (!reach_finish[w]) {
        reach_finish[w] = true;
        todo.push_back(w);
      }
    }
  }

  // The problem statement guarantees this:
  assert(reach_start[V - 1] && reach_finish[0]);

  // Remove all edges that are not reachable from both the start and the finish,
  // since they cannot lie on the path from start to finish. Doing this means
  // that if we find a positive-score cycle below, it must lie on the path from
  // start to finish.
  //
  // (In theory we could also remove unreachable vertices to decrease V, but
  // it doesn't change the worst-case time complexity.)
  {
    vector<Edge> new_edges;
    for (const Edge &e : edges) if (reach_start[e.v] && reach_finish[e.w]) new_edges.push_back(e);
    new_edges.swap(edges);
  }

  // Bellman-Ford to find maximal path to the finish and detect positive-score
  // cycles in the graph.
  constexpr int64_t inf = 1e18;
  vector<int64_t> score(V, -inf);
  score[0] = 0;
  REP(n, V - 1) for (auto [v, w, c] : edges) score[w] = max(score[w], score[v] + c);
  for (auto [v, w, c] : edges) if (score[v] + c > score[w]) return -1;  // cycle detected!
  return score[V - 1];
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << Solve() << endl;

}
