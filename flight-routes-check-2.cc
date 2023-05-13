// Flight Routes Check
// https://cses.fi/problemset/task/1682
//
// Solution: decompose into strongly connected components.
// If there is a path between any pair of cities, then there is a single SCC.

#include <bits/stdc++.h>

#include "strongly-connected-components.h"

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  vector<vector<int>> adj(V);
  for (int e = 0; e < E; ++e) {
    int a = 0, b = 0;
    cin >> a >> b;
    adj[a - 1].push_back(b - 1);
  }

  vector<vector<int>> components = CalculateStronglyConnectedComponents(adj);
  if (components.size() < 2) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
    cout << components[0][0] + 1 << ' '  << components[1][0] + 1 << '\n';
  }
}
