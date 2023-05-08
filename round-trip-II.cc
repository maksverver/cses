// Round Trip II
// https://cses.fi/problemset/task/1678
//
// Problem:
//
// Find a cycle in a directed graph.
//
// Solution:
//
// We can recursively remove dead-ends (nodes with outdegree 0). Then we can
// start from an arbitrary remaining node to find a cycle. This works since
// all remaining vertices have outdgree > 0, so we can always find a successor,
// and since the number of vertices is finite, we will eventually create a
// cycle.
//
// See also round-trip.cc for the undirected version of this problem.

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

  int V = 0, E = 0;
  cin >> V >> E;
  vector<int> outdegree(V);
  vector<vector<int>> prev(V);  // forward edge list
  vector<vector<int>> next(V);  // backward edge list
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    next[a].push_back(b);
    prev[b].push_back(a);
    ++outdegree[a];
  }

  vector<char> deleted(V, false);
  vector<int> todo;
  REP(v, V) if (outdegree[v] == 0) {
    deleted[v] = true;
    todo.push_back(v);
  }
  while (!todo.empty()) {
    int v = todo.back();
    todo.pop_back();
    for (int w : prev[v]) {
      assert(!deleted[w] && outdegree[w] > 0);
      if (--outdegree[w] == 0) {
        deleted[w] = true;
        todo.push_back(w);
      }
    }
  }

  // Returns an arbitrary (but deterministic) successor of v.
  auto successor = [&](int v) {
    for (int w : next[v]) if (!deleted[w]) return w;
    assert(false);
    return -1;
  };

  vector<int> path;
  REP(v, V) if (!deleted[v]) {
    // Find the starting point of the cycle.
    vector<char> seen(V, false);
    while (!seen[v]) {
      seen[v] = true;
      v = successor(v);
    }
    // Reconstruct the list of vertices on the cycle.
    path.push_back(v + 1);
    for (int w = successor(v); w != v; w = successor(w)) path.push_back(w + 1);
    path.push_back(v + 1);
    break;
  }
  if (path.empty()) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << path.size() << '\n' << path << endl;
  }
}
