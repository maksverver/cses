// Cycle Finding
// https://cses.fi/problemset/task/1197
//
// Solution: Bellman-Ford
//
// Since we can start from any vertex, we set all the initial distances to 0
// (instead of setting distances to infinity, except for the start).

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

struct Edge {
  int v, w, c;
};

static void Solve() {
  int V = 0, E = 0;
  cin >> V >> E;
  vector<Edge> edges(E);
  for (auto &[v, w, c] : edges) {
    cin >> v >> w >> c;
    --v, --w;
  }
  vector<int64_t> dist(V, 0);
  vector<int> prev(V, -1);
  REP(n, V) {
    bool changed = false;
    for (auto [v, w, c] : edges) if (dist[v] + c < dist[w]) {
      changed = true;
      dist[w] = dist[v] + c;
      prev[w] = v;
      if (n == V - 1) {
        // Cycle detected! Reconstructing the cycle is mildly tricky, because
        // the edge (v, w) isn't necessarily part of the cycle, but it must be
        // reachable from it. So use a cycle-finding algorithm to find a vertex
        // that lies on the cycle:
        std::vector<char> visited(V);
        visited[w] = true;
        while (!visited[v]) {
          visited[v] = true;
          v = prev[v];
          assert(v != -1);
        }
        // Vertex v lies on the cycle. Now reconstruct the actual cycle.
        std::vector<int> cycle;
        cycle.push_back(v + 1);
        for (int u = prev[v]; u != v; u = prev[u]) cycle.push_back(u + 1);
        cycle.push_back(v + 1);
        std::reverse(cycle.begin(), cycle.end());
        cout << "YES\n" << cycle << '\n';
        return;
      }
    }
    if (!changed) break;  // early-out
  }
  cout << "NO\n";
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  Solve();
}
