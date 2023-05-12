// Road Construction
// https://cses.fi/problemset/task/1676
//
// Disjoint-set (union-find) data structure, with slight modifications to keep
// track of the number of disjoint sets and the maximum set size.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

/* UNION-FIND DATASTRUCTURE

   Keeps track of a partition of elements (identified by integers in the range
   0 to count) into disjoint sets.

   Union and find operations run in 'almost' constant amortized time. */
struct UnionFind {
  vector<pair<int, int> > pr;
  /* first:  parent node */
  /* second: rank (number of nodes in subtree */

  int num_sets;
  int max_rank;

  /* Constructs a union-find datastructure, consisting of 'nodes' distinct
      sets of one node each. */
  UnionFind(int nodes) {
    pr.reserve(nodes);
    REP(n, nodes) pr.push_back(make_pair(n, 1));
    num_sets = nodes;
    max_rank = 1;
  }

  /* Combines the distinct sets to which u and v belong and returns true,
      or returns false if u and v were already in the same set. */
  bool combine(int u, int v) {
    if((u = find(u)) != (v = find(v))) {
      if(pr[u].second < pr[v].second) swap(u, v);
      pr[u].second += pr[v].second; /* update rank of set of u */
      pr[v].first  = u;             /* add v to set of u */
      max_rank = max(max_rank, pr[u].second);
      --num_sets;
      return true;
    }
    return false;
  }

  /* Returns a set identifier for v, so that find(u) == find(v) if
      u and v are in the same set. */
  int find(int v) {
    if (pr[v].first == v) return v;
    return pr[v].first = find(pr[v].first);
  }
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  UnionFind uf(N);
  REP(_, M) {
    int a = 0, b = 0;
    cin >> a >> b;
    uf.combine(a - 1, b - 1);
    cout << uf.num_sets << ' ' << uf.max_rank << '\n';
  }
}
