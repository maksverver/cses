// Coin Collector
// https://cses.fi/problemset/task/1686
//
// Problem:
//
// Given a directed graph with V vertices and E edges, where each vertex
// has a number of coins C[v] associated with it that can be collected by
// visiting that vertex (by only once), what is the maximum number of coins we
// can collect, starting and ending at any vertex?
//
// Solution:
//
// Decomposition into strongly connected components.
//
// Since all coin values are positive, if we enter a strongly-connected
// component, we can and should collect all coins in that component.
//
// If we contract each component into a single vertex, the remaining graph is
// a directed acyclic graph (DAG), so we can process components in reverse
// topological order. Then the value of a component is the sum of the coins in
// this component plus the maximum value of a component directly reachable from
// this component. The answer is the maximum value of a component.

#include <bits/stdc++.h>

using namespace std;

#include "strongly-connected-components.h"

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  vector<int> C(V);
  for (int &x : C) cin >> x;
  vector<vector<int>> adj(V);
  for (int e = 0; e < E; ++e) {
    int a = 0, b = 0;
    cin >> a >> b;
    adj[a - 1].push_back(b - 1);
  }

  // Note: the algorithm below requires that `components` are returned in
  // reverse topological order!
  vector<vector<int>> components = CalculateStronglyConnectedComponents(adj);

  vector<int> vertex_component(V, -1);
  vector<int64_t> component_value(components.size(), 0);
  int64_t answer = 0;
  for (int i = 0; i < components.size(); ++i) {
    for (int v : components[i]) vertex_component[v] = i;
    int64_t this_value = 0;
    int64_t next_value = 0;
    for (int v : components[i]) {
      this_value += C[v];
      for (int w : adj[v]) if (int j = vertex_component[w]; j != i) {
        next_value = std::max(next_value, component_value[j]);
      }
    }
    component_value[i] = this_value + next_value;
    answer = max(answer, component_value[i]);
  }

  cout << answer << endl;
}
