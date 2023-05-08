// Flight Discount
// https://cses.fi/problemset/task/1195
//
// Solution: Dijkstra's algorithm on a slightly modified graph.
//
// Basically we clone the graph, creating one subgraph where we still have
// the ticket and a second subgraph where we have used to the ticket. Each
// subgraph has all the edges in the input, but there are also edges to go
// from a vertex in the first subgraph to the corresponding vertex in the
// second subgraph at half the cost.
//
// More formally, for the input graph G with vertex set V and edge set E
// we create G' with vertex set V' = {(v, 0), (v, 1) for all v in V} and
// edge set E = {((v0, 0), (w0, 0), c), ((v0, 1), (w0, 1), c),
// ((v0, 1), (w0, 0), c/2) for all (v, w, c) in E}.
//
// Then we search for the minimum cost path from (1, 1) to (N, 0)
// (we can assume we always use the ticket because N > 1 and using a ticket
// is never worse than not using a ticket).
//
// Solution: Dijkstra's algorithm.
// Complexity: O(V + E log E) time, O(V + E) space.

#include <bits/stdc++.h>

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

  // We encode the states as ((vertex << 1) | ticket_used), i.e., the
  // least-significant bit indicates whether we can use the discount ticket
  // and the remaining bits encode the current vertex.
  const int64_t inf = 1e18;
  vector<int64_t> dist(2*V, inf);
  std::priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> todo;
  dist[0] = 0;
  todo.push({0, 0});
  while (!todo.empty()) {
    auto [d, s] = todo.top();
    todo.pop();
    if (d != dist[s]) continue;
    int v = s >> 1;
    for (auto [w, c] : adj[v]) {
      int t = (w << 1) | (s & 1);
      if (c + d < dist[t]) {
        dist[t] = c + d;
        todo.push({c + d, t});
      }
      if ((s & 1) == 0) {
        t ^= 1;
        c /= 2;
        if (c + d < dist[t]) {
          dist[t] = c + d;
          todo.push({c + d, t});
        }
      }
    }
  }
  cout << dist[2*V - 1] << '\n';
}
