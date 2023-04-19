// Building Teams
// https://cses.fi/problemset/task/1668
//
// Solution:
//
// The friendship graph is a simple graph with (possibly) multiple connected
// components. Within a component we can follow edges and assign people to
// alternating teams.
//
// It doesn't matter which team the initial person in a component is assigned to
// since by definition nobody in one component is friends with a person in
// another component.

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

  vector<int> team(N);
  deque<int> todo;
  REP(v, N) if (!team[v]) {
    team[v] = 1;
    todo.push_back(v);
    while (!todo.empty()) {
      int v = todo.front();
      todo.pop_front();
      for (int w : adj[v]) {
        if (team[w] == 0) {
          team[w] = 3 - team[v];
          todo.push_back(w);
        } else if (team[w] == team[v]) {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
      }
    }
  }
  cout << team << '\n';
}
