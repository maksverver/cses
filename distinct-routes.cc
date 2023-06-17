// Distinct Routes
// https://cses.fi/problemset/task/1711
//
// Max-flow problem.
//
// The number of days we can play is equal to the maximum flow. Then we only
// need to reconstruct independent augmenting paths.

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

/* Minimum-cost maximum flow implementation starts here. */

typedef int cost_t;
typedef int flow_t;

// "infinite" cost/flow values. Must be larger than any legtimate value,
// while being small enough such that inf+inf doesn't overflow!
const cost_t inf_cost = 1e9;
const flow_t inf_flow = 1e9;

struct Edge {
  Edge(int src, int dst, cost_t cost, flow_t cap)
      : src(src), dst(dst), cost(cost), cap(cap), flow(0) { }

  int src, dst;
  cost_t cost;
  flow_t cap, flow;
};

struct MinCostMaxFlow {
protected:
  vector<Edge> edges;
  int V, S, T;
  cost_t cst;
  flow_t flw;

public:
  /* Compute the minimum-cost maximum-flow over the given edges.

      The return value is a pair of minimum cost and maximum flow. The list
      of edges is updated to reflect the optimal flow.

      Complexity: O(max_flow*V*E) time, O(V) space
      (but only if flow_t is integer!)
  */
  pair<cost_t,flow_t> operator()(vector<Edge> &edges, int S, int T) {
    if (S == T) return make_pair(0, inf_flow);

    this->S = S;
    this->T = T;

    // Determine number of vertices
    V = max(S, T);
    for (size_t n = 0; n < edges.size(); ++n) {
      assert(edges[n].cost >= cost_t(0));
      assert(edges[n].cap  >= flow_t(0));
      assert(edges[n].flow == flow_t(0));
      V = max(V, max(edges[n].src, edges[n].dst));
    }
    ++V;

    // Determine max. flow by computing cheapest augmenting paths
    cst = 0;
    flw = 0;
    this->edges.swap(edges);
    while (augment()) { };
    this->edges.swap(edges);
    return make_pair(cst, flw);
  }

protected:
  // Search for a minimum-cost augmenting path using Bellman-Ford. If a path
  // is found, the flow is augmented and true is returned.
  // Complexity: O(V*E) time, O(V) space */
  bool augment() {
    vector<cost_t> cost(V, inf_cost);
    vector<int> edge(V, 0);
    cost[S] = 0;
    bool changed = true;
    // NB: assumes no negative weight cycles are present, or this will loop
    //     indefinitely! (or until integer overflow occurs)
    while (changed) {
      changed = false;
      for (size_t n = 0; n < edges.size(); ++n) {
        const Edge &e = edges[n];
        if (e.flow < e.cap && cost[e.src] + e.cost < cost[e.dst]) {
          cost[e.dst] = cost[e.src] + e.cost;
          edge[e.dst] = n + 1;
          changed = true;
        }
        if (e.flow > 0 && cost[e.dst] - e.cost < cost[e.src]) {
          cost[e.src] = cost[e.dst] - e.cost;
          edge[e.src] = -(n + 1);
          changed = true;
        }
      }
    }
    if (cost[T] == inf_cost) return false;

    // Find minimum flow over all edges
    flow_t f = inf_flow;
    for (int n = edge[T]; n != 0; ) {
      const Edge &e = edges[abs(n) - 1];
      f = min(f, n > 0 ? e.cap - e.flow : e.flow);
      n = edge[n > 0 ? e.src : e.dst];
    }
    assert(f > flow_t(0));

    // Augment flow
    for (int n = edge[T]; n != 0; ) {
      Edge &e = edges[abs(n) - 1];
      if (n > 0) e.flow += f, cst += e.cost*f;
      if (n < 0) e.flow -= f, cst -= e.cost*f;
      n = edge[n > 0 ? e.src : e.dst];
    }
    flw += f;
    return true;
  }
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int V = 0, E = 0;
  cin >> V >> E;
  vector<Edge> edges;
  while (E--) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    edges.push_back(Edge(v, w, 0, 1));
  }

  MinCostMaxFlow mcmf;
  cout << mcmf(edges, 0, V - 1).second << '\n';

  // Greedily reconstruct augmenting paths.
  vector<vector<int>> adj(V);
  for (const Edge &e : edges) if (e.flow) adj[e.src].push_back(e.dst);
  while (!adj[0].empty()) {
    vector<int> path;
    int v = 0;
    path.push_back(v + 1);
    while (v != V - 1) {
      assert(!adj[v].empty());
      int w = adj[v].back();
      adj[v].pop_back();
      v = w;
      path.push_back(v + 1);
    }
    cout << path.size() << '\n' << path << '\n';
  }
}
