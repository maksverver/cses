// Round Trip
// https://cses.fi/problemset/task/1669
//
// Problem: Given a simple graph, find a simple cycle of at least length 3.
//
// Solution: DFS from each connected component; avoid revisiting the immediate
// parent of each vertex. If we can revisit another vertex there is a cycle in
// the graph.
//
// Proof that this works: let x be the vertex in a cycle that is closest to the
// root (where we start the DFS). Then x must have two children, a and b, such
// that there is a path between a and b that does not go through x. In that case,
// the DFS will find the path x-a-...-b, and when visiting b, will find the
// connection back to x.
//
// Note that this is only guaranteed to find *a* cycle, not the longest cycle.
// For example, V=4:
//
//   1---2
//   | / |
//   3---4
//
// We can find the cycle 1-2-3, 2-4-3, or 1-2-4-3, depending on the order in
// which neighbors are visited.
//
// Note that finding the longest cycle in a graph (or a cycle of given length K)
// is an NP-hard problem.
//
// See also round-trip-II.cc for the directed version of this problem, but
// without the constraint on cycle length.

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

int V, E;
vector<vector<int>> adj;
vector<int> prev;

int Dfs(int v, int u) {
  int old_prev = prev[v];
  prev[v] = u;

  // Vertex revisited -> cycle detected!
  if (old_prev != -1) return v;

  for (int w : adj[v]) if (w != u) {
    int res = Dfs(w, v);
    if (res != -1) return res;
  }
  return -1;
}

int FindCycleStart() {
  prev.assign(V, -1);
  int res = -1;
  REP(v, V) if (prev[v] == -1) {
    // Search connected component.
    res = Dfs(v, v);
    if (res != -1) break;
  }
  return res;
}

void Solve() {
  int v = FindCycleStart();

  if (v == -1) {
    cout << "IMPOSSIBLE\n";
  } else {
    // Cycle found. Reconstruct solution.
    vector<int> answer;
    answer.push_back(v + 1);
    for (int w = prev[v]; w != v; w = prev[w]) {
      answer.push_back(w + 1);
    }
    answer.push_back(v + 1);
    cout << answer.size() << '\n' << answer << '\n';
  }
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  cin >> V >> E;
  adj.resize(V);
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  Solve();
}
