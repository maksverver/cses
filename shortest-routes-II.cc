// Shortest Routes II
// https://cses.fi/problemset/task/1672
//
// Problem: given a weighted undirected graph, find the shortest path between
// all pairs of vertices.
//
// Solution: Floyd-Warshall
// Complexity: O(V^3 + E) time, O(V^2) space.

#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0, Q = 0;
  cin >> V >> E >> Q;

  const int64_t inf = 1e18;
  vector<vector<int64_t>> dist(V, vector<int64_t>(V, inf));
  REP(v, V) dist[v][v] = 0;

  REP(_, E) {
    int a = 0, b = 0;
    int64_t c = 0;
    cin >> a >> b >> c;
    --a, --b;
    dist[a][b] = min(dist[a][b], c);
    dist[b][a] = min(dist[b][a], c);
  }

  // Floyd-Warshall algorithm to find all shortest paths.
  //
  // The invariant is this: after k iterations, we have found all shortest paths
  // beteen i and j using only intermediate vertices < k.
  REP(k, V) REP(i, V) REP(j, V) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  REP(_, Q) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    cout << (dist[a][b] == inf ? -1 : dist[a][b]) << '\n';
  }
}
