// Investigation
// https://cses.fi/problemset/task/1202
//
// Solution: Dijkstra's algorithm.
//
// This works since Dijkstra's algorithm fixes the minimum-cost paths
// in nonincreasing order, and since all costs are greater than 0, that
// means when we fix a vertex `v` min_cost[v] = d, we can calculate
// num_routes[v], min_length[v], and max_length[v] based on the values of its
// predecessors, which must necessarily already have been computed.
//
// See also: flight-routes.cc.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Edge {
  int w, c;
};

struct State {
  int64_t cost;
  int v;
};

bool operator<(const State &s, const State &t) {
  return s.cost > t.cost;
}

constexpr int MOD = 1e9 + 7;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  vector<vector<Edge>> incoming(V);
  vector<vector<Edge>> outgoing(V);
  for (int e = 0; e < E; ++e) {
    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    --a, --b;
    incoming[b].push_back(Edge{a, c});
    outgoing[a].push_back(Edge{b, c});
  }

  vector<int64_t> min_cost(V, (int64_t) 1e18);
  vector<int> num_routes(V, 0);
  vector<int> min_length(V, V + 1);
  vector<int> max_length(V, 0);

  std::priority_queue<State> todo;
  min_cost[0] = 0;
  num_routes[0] = 1;
  min_length[0] = 0;
  max_length[0] = 0;
  for (auto [v, c] : outgoing[0]) todo.push({c, v});

  while (!todo.empty()) {
    auto [d, v] = todo.top();
    todo.pop();
    if (d >= min_cost[v]) continue;
    assert(min_cost[v] == (int64_t) 1e18);
    min_cost[v] = d;
    for (auto [u, c] : incoming[v]) if (min_cost[u] + c == d) {
      num_routes[v] = (num_routes[v] + num_routes[u]) % MOD;
      min_length[v] = min(min_length[v], min_length[u] + 1);
      max_length[v] = max(max_length[v], max_length[u] + 1);
    }

    for (auto [w, c] : outgoing[v]) todo.push({c + d, w});
  }

  cout << min_cost[V - 1] << ' ' << num_routes[V - 1] << ' ' << min_length[V - 1] << ' ' << max_length[V - 1] << endl;
}
