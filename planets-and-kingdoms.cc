// Planets and Kingdoms
// https://cses.fi/problemset/task/1683
//
// Solution: standard decomposition into strongly-connected components.

#include <bits/stdc++.h>

#include "strongly-connected-components.h"

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
  vector<vector<int>> adj(V);
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    adj[a - 1].push_back(b - 1);
  }

  vector<vector<int>> components = CalculateStronglyConnectedComponents(adj);

  vector<int> labels(V);
  REP(i, components.size()) {
    for (int v : components[i]) {
      labels[v] = i + 1;
    }
  }
  cout << components.size() << '\n' << labels << endl;
}
