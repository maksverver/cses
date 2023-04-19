// Building Roads
// https://cses.fi/problemset/task/1666
//
// Problem:
//
// Given a simple undirected graph, calculate how many edges need to be added
// to make the graph fully connected.
//
// Solution:
//
// Use DFS/BFS to identify connected components. Then build a road between
// consecutive pairs of components, using a representative city from each
// component (it doesn't matter which one since we can print any solution).

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;

  vector<vector<int>> adj(N);
  REP(m, M) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> roots;
  vector<char> reachable(N, false);
  REP(v, N) if (!reachable[v]) {
    roots.push_back(v);
    deque<int> todo;
    reachable[v] = true;
    todo.push_back(v);
    while (!todo.empty()) {
      int v = todo.front();
      todo.pop_front();
      for (int w : adj[v]) if (!reachable[w]) {
        reachable[w] = true;
        todo.push_back(w);
      }
    }
  }

  assert(!roots.empty());  // since N > 0
  cout << roots.size() << '\n';
  REP(i, roots.size() - 1) cout << roots[i] + 1 << ' ' << roots[i + 1] + 1 << '\n';
}
