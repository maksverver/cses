// Shortest Routes I
// https://cses.fi/problemset/task/1671
//
// Problem: given a weighted directed graph, find the shortest path from
// a single source to all destinations.
//
// Solution: Dijkstra's algorithm.
// Complexity: O(V + E log E) time, O(V + E) space.

#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) {
    if (i > 0) os << ' ';
    os << v[i];
  }
  return os;
}

namespace {

struct Edge {
  int w, c;
};

int V, E;
vector<vector<Edge>> adj;

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  cin >> V >> E;
  adj.resize(V);
  REP(_, E) {
    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    --a, --b;
    adj[a].push_back(Edge{b, c});
  }

  const int64_t inf = 1e18;
  vector<int64_t> dist(V, inf);
  std::priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> todo;
  dist[0] = 0;
  todo.push({0, 0});
  while (!todo.empty()) {
    auto [d, v] = todo.top();
    todo.pop();
    if (d != dist[v]) continue;
    for (auto [w, c] : adj[v]) {
      if (c + d < dist[w]) {
        dist[w] = c + d;
        todo.push({c + d, w});
      }
    }
  }
  cout << dist << '\n';
}
