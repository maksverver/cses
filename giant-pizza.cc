// Giant Pizza
// https://cses.fi/problemset/task/1684
//
// Problem:
// 2SAT (Boolean satisfiability)
//
// Solution:
// Via strongly connected components
// See: https://sci-hub.se/10.1016/0020-0190(79)90002-4
//
// For each variable x, we create two vertexes corresponding with x and !x.
// (For the i-th variable, we create vertices 2*i and 2*i+1 for false and true.)
// Then for each constraint (a || b) we create edges in the implication graph
// corresponding with !a -> b and !b -> a.
//
// A solution exists if and only if a variable does not appear in the same
// strongly connected component as its negation. In that case, we can assign
// variables in reverse topological order.

#include <bits/stdc++.h>

#include "strongly-connected-components.h"

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  // N equations over M variables
  int N = 0, M = 0;
  cin >> N >> M;
  vector<vector<int>> adj(2*M);
  REP(n, N) {
    char sign1, sign2;
    int value1, value2;
    cin >> sign1 >> value1 >> sign2 >> value2;
    assert(sign1 == '+' || sign1 == '-');
    assert(1 <= value1 && value1 <= M);
    assert(sign2 == '+' || sign2 == '-');
    assert(1 <= value2 && value2 <= M);

    int p = 2*(value1 - 1) + (sign1 == '+');
    int q = 2*(value2 - 1) + (sign2 == '+');

    adj[p ^ 1].push_back(q);
    adj[q ^ 1].push_back(p);
  }

  vector<vector<int>> components = CalculateStronglyConnectedComponents(adj);

  vector<int> component_index(2*M, -1);
  REP(i, components.size()) {
    for (int v : components[i]) component_index[v] = i;
  }

  REP(i, M) if (component_index[2*i] == component_index[2*i + 1]) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  vector<int> values(2*M, -1);
  for (const auto &component : components) {
    for (int v : component) {
      if (values[v] == -1) {
        assert(values[v^1] == -1);
        values[v] = true;
        values[v^1] = false;
      }
    }
  }

  REP(i, M) {
    if (i > 0) cout << ' ';
    cout << (values[2*i + 1] ? '+' : '-');
  }
  cout << endl;
}
