// Message Route
// https://cses.fi/problemset/task/1667
//
// Solution: BFS/DFS on a simple graph.

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

  vector<int> prev(N, -1);
  deque<int> todo;
  prev[N - 1] = 0;
  todo.push_back(N - 1);
  while (!todo.empty()) {
    int v = todo.front();
    todo.pop_front();
    for (int w : adj[v]) if (prev[w] == -1) {
      prev[w] = v;
      if (w > 0) {
        todo.push_back(w);
      } else {
        // Solution found. Reconstruct path.
        vector<int> path;
        int v = w;
        do {
          path.push_back(v + 1);
          v = prev[v];
        } while (v != 0);
        cout << path.size() << '\n' << path << '\n';
        return 0;
      }
    }
  }
  cout << "IMPOSSIBLE\n";
}
