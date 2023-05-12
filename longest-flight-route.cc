// Longest Flight Route
// https://cses.fi/problemset/task/1680
//
// Solution: topological sorting.

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
  vector<int> num_incoming(N + 1);
  vector<vector<int>> incoming_flights(N + 1);
  vector<vector<int>> outgoing_flights(N + 1);
  for (int m = 0; m < M; ++m) {
    int a = 0, b = 0;
    cin >> a >> b;

    num_incoming[b]++;
    incoming_flights[b].push_back(a);
    outgoing_flights[a].push_back(b);
  }

  // max_visit[x] == maximum number of cities in a trip from 1 to x
  vector<int> max_visit(N + 1, -1);
  // prev_city[x] == previous city visited in the maximal trip ending at x
  vector<int> prev_city(N + 1, -1);
  vector<int> order;
  for (int i = 1; i <= N; ++i) {
    if (num_incoming[i] == 0) order.push_back(i);
  }
  max_visit[1] = 1;
  for (size_t i = 0; i < order.size(); ++i) {
    int b = order[i];
    for (int a : incoming_flights[b]) {
      // Calculate maximum number of cities we can visit starting from 1
      // and ending at `b`.
      if (max_visit[a] != -1 && max_visit[b] < max_visit[a] + 1) {
        max_visit[b] = max_visit[a] + 1;
        prev_city[b] = a;
      }
    }
    for (int c : outgoing_flights[b]) {
      if (--num_incoming[c] == 0) order.push_back(c);
    }
  }

  if (max_visit[N] == -1) {
    // No path from 1 to N.
    cout << "IMPOSSIBLE" << endl;
  } else {
    // Reconstruct path.
    vector<int> path;
    for (int n = N; n != -1; n = prev_city[n]) path.push_back(n);
    reverse(path.begin(), path.end());
    cout << path.size() << '\n' << path << endl;
  }
}
