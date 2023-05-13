// Flight Routes Check
// https://cses.fi/problemset/task/1682
//
// Solution:
//
// Consider the directed graph G given in the input, and the transpose graph G'
// obtained by flipping the direction of all edges.
//
// Now pick an arbitary vertex v. We can use a DFS/BFS on G to determine the
// vertices reachable from v, and a DFS/BFS on G' to determine the vertices from
// which G can be reached. It's a necessary condition that both vertex sets
// must be V (or we have found a counter-example: a vertex that is not
// reachable from V, or a vertex from which V cannot be reached). If both sets
// are equal to V, then the graph is fully connected, because for any other
// pair of vertices (x, y), there must be (at least) a path from x to y that
// goes through v.
//
// It's also possible to solve the problem by decomposing the graph into
// strongly connected components (see flight-routes-check-2.cc). Both solutions
// take O(V + E) time and space.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

static int ComputeReachability(const vector<vector<int>> &adj, int start, vector<char> &reachable) {
  reachable.assign(adj.size(), false);
  vector<int> todo;
  reachable[start] = true;
  todo.push_back(start);
  for (size_t i = 0; i != todo.size(); ++i) {
    int v = todo[i];
    for (int w : adj[v]) {
      if (!reachable[w]) {
        reachable[w] = true;
        todo.push_back(w);
      }
    }
  }
  return todo.size();
}

static int Unreachable(vector<char> &reachable) {
  int i = 0;
  while (i != reachable.size() && reachable[i]) ++i;
  return i;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  vector<vector<int>> outgoing(V + 1);
  vector<vector<int>> incoming(V + 1);
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    outgoing[a].push_back(b);
    incoming[b].push_back(a);
  }

  vector<char> reachable;
  if (ComputeReachability(outgoing, 0, reachable) != V) {
    cout << "NO\n" << 1 << ' ' << Unreachable(reachable) + 1 << endl;
  } else if (ComputeReachability(incoming, 0, reachable) != V) {
    cout << "NO\n" << Unreachable(reachable) + 1 << ' ' << 1 << endl;
  } else {
    cout << "YES" << endl;
  }
}
