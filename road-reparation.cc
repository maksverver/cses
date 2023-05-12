// Road Reparation
// https://cses.fi/problemset/task/1675
//
// Problem: classical minimum spanning tree (MST)
// Solution: Kruskal's algorithm (alternative: Prim's algorithm)

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

/* UNION-FIND DATASTRUCTURE

   Keeps track of a partition of elements (identified by integers in the range
   0 to count) into disjoint sets.

   Union and find operations run in 'almost' constant amortized time. */
class UnionFind {
  vector<pair<int, int> > pr;
  /* first:  parent node */
  /* second: rank (number of nodes in subtree */

public:
  /* Constructs a union-find datastructure, consisting of 'nodes' distinct
      sets of one node each. */
  UnionFind(int nodes) {
    pr.reserve(nodes);
    REP(n, nodes) pr.push_back(make_pair(n, 1));
  }

  /* Combines the distinct sets to which u and v belong and returns true,
      or returns false if u and v were already in the same set. */
  bool combine(int u, int v) {
    if((u = find(u)) != (v = find(v))) {
      if(pr[u].second < pr[v].second) swap(u, v);
      pr[u].second += pr[v].second; /* update rank of set of u */
      pr[v].first  = u;             /* add v to set of u */
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

  /* Returns the number of disjount sets (by counting, so it's slow). */
  int count() {
    int res = 0;
    for (int i = 0; i < pr.size(); ++i) {
      if (pr[i].first == i) ++res;
    }
    return res;
  }
};

struct Edge {
  int a, b, c;
};

bool operator<(const Edge &a, const Edge &b) {
  return a.c < b.c;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  vector<Edge> edges;

  int N = 0, M = 0;
  cin >> N >> M;
  REP(_, M) {
    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    edges.push_back(Edge{a - 1, b - 1, c});
  }

  std::sort(edges.begin(), edges.end());

  int64_t answer = 0;
  UnionFind uf(N);
  for (auto [a, b, c] : edges) {
    if (uf.combine(a, b)) answer += c;
  }

  if (uf.count() > 1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << answer << endl;
  }
}
