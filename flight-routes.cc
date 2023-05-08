// Flight Routes
// https://cses.fi/problemset/task/1196
//
// Problem:
//
// Given a weighted directed graph on V vertices and a number K (K ≤ 10),
// find the lengths of the K shortest paths from 1 to V.
//
// Solution:
//
// Dijkstra's algorithm, modified to keep track of the top K shortest paths,
// and allowing nodes to be revisited.
//
// Complexity: O(V + EK log EK) time, O(VK) space.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Edge {
  int w, c;
};

struct State {
  int64_t dist;
  int v;
};

bool operator<(const State &s, const State &t) {
  return s.dist > t.dist;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0, K = 0;
  cin >> V >> E >> K;
  vector<vector<Edge>> adj(V);
  for (int e = 0; e < E; ++e) {
    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    --a, --b;
    adj[a].push_back(Edge{b, c});
  }

  // For each vertex, we will keep the top K shortest distances.
  vector<int64_t> dist(V*K, (int64_t) 1e18);
  vector<int> visited(V, 0);

  std::priority_queue<State> todo;
  todo.push(State{0, 0});
  while (!todo.empty()) {
    auto [d, v] = todo.top();
    todo.pop();

    if (visited[v] == K) continue;
    dist[v*K + visited[v]++] = d;

    for (auto [w, c] : adj[v]) todo.push({c + d, w});
  }

  // Print output. We can assume all K distances are less than infinity.
  for (int k = 0; k < K; ++k) {
    if (k > 0) cout << ' ';
    cout << dist[(V - 1)*K + k];
  }
  cout << endl;
}
