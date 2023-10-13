// Tree Diameter
// https://cses.fi/problemset/task/1131/
//
// The diameter of a graph is defined as the maximum length of a shortest path
// between any pair of vertices. To calculate the diameter of a tree:
//
//  - Start from an arbitrary vertex u.
//  - Let v be a vertex at maximum distance from u.
//  - Let w be a vertex at maximum distance from v.
//
// Then the distance from v to w is maximal. The farthest vertices can be found
// easily with a breadth-first search (or, if stack space is not a concern, with
// a depth-first search).
//
// This feels intuitive but it is not trivial to prove formally.
// Some pointers here: https://codeforces.com/blog/entry/60440
//
// See also tree-diameter-2.cc for a version uses dynamic programming (DP) on
// the tree instead. This is more complicated to implement, but easier to prove
// correct, and runs with the same time complexity.

#include <bits/stdc++.h>

using namespace std;

int N;
vector<vector<int>> adj;

// Searches for a vertex at maximum distance of `start` and returns a
// pair {vertex, distance}.
//
// This just does a single-source breadth-first search (BFS), which works for
// arbitrary graphs, not just trees!
pair<int, int> FindFarthestVertex(int start) {
  vector<int> dist(N, -1);
  dist[start] = 0;
  vector<int> todo;
  todo.push_back(start);
  for (size_t i = 0; i != todo.size(); ++i) {
    int v = todo[i];
    for (int w : adj[v]) if (dist[w] == -1) {
      dist[w] = dist[v] + 1;
      todo.push_back(w);
    }
  }
  int v = todo.back();
  return {v, dist[v]};
}

int Solve() {
  int v = FindFarthestVertex(0).first;
  int d = FindFarthestVertex(v).second;
  return d;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  N = 0;
  cin >> N;
  adj = vector<vector<int>>(N);
  for (int e = 0; e < N - 1; ++e) {
    int u = 0, v = 0;
    cin >> u >> v;
    --u, --v;
    assert(u != v && 0 <= u && u < N && 0 <= v && v < N);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  cout << Solve() << endl;
}
