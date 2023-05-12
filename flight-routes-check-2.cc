// Flight Routes Check
// https://cses.fi/problemset/task/1682
//
// Solution: decompose into strongly connected components.
// If there is a path between any pair of cities, then there is a single SCC.

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

// Tarjan's algorithm for finding Strongly Connected Components
// https://sci-hub.se/10.1137/0201010
//
// Given a directed graph as an adjacency list, partitions the vertices into
// strongly connected components, which are returned in reverse topological
// order (i.e., if a one component is reachable from another, then the former
// appears before the latter in the result).
//
// This can also be modified to return the components one-by-one.
static vector<vector<int>>
CalculateStronglyConnectedComponents(const vector<vector<int>> &adj) {

  struct Impl {
    const vector<vector<int>> &adj;
    vector<vector<int>> &components;
    vector<int> number;
    vector<int> lowlink;
    vector<int> stack_pos;
    vector<int> next_child;
    int next_number = 0;
    vector<int> stack;
    vector<pair<int, int>> call_stack;  // list of {vertex, child index} pairs

    Impl(const vector<vector<int>> &adj, vector<vector<int>> &components) :
        adj(adj), components(components),
        number(adj.size(), -1), lowlink(adj.size(), -1),
        stack_pos(adj.size(), -1), next_child(adj.size(), -1) {
    }

    // TODO: change this to not actually use recursion!
    void Dfs(int v) {
      number[v] = lowlink[v] = next_number++;
      stack_pos[v] = stack.size();
      stack.push_back(v);
      for (int w : adj[v]) {
        if (number[w] == -1) {
          Dfs(w);
          lowlink[v] = std::min(lowlink[v], lowlink[w]);
        } else if (stack_pos[w] != -1) {
          lowlink[v] = std::min(lowlink[v], number[w]);
        }
      }
      if (lowlink[v] == number[v]) {
        // New strongly-connected component found!
        int pos = stack_pos[v];
        components.push_back(vector(stack.begin() + pos, stack.end()));
        while (stack.size() > pos) {
          stack_pos[stack.back()] = -1;
          stack.pop_back();
        }
      }
    }
  };

  vector<vector<int>> components;
  Impl(adj, components).Run();
  return components;
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
  if (components.size() < 2) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
    cout << components[0][0] + 1 << ' '  << components[1][0] + 1 << '\n';
  }
}
