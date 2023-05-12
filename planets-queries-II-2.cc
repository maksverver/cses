// Planets Queries II
// https://cses.fi/problemset/task/1160
//
// This is an O(N) optimized version of planets-queries-II.cc.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Query {
  int a, b, answer;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> next(N);
  for (int &x : next) cin >> x, --x;
  vector<Query> queries(Q);
  for (auto &q : queries) {
    cin >> q.a >> q.b;
    q.answer = -2;
    --q.a, --q.b;
  }
  vector<vector<Query*>> queries_by_source(N);
  for (auto &q : queries) queries_by_source[q.a].push_back(&q);

  vector<int> indegree(N);
  REP(i, N) ++indegree[next[i]];
  vector<char> seen(N, false);
  vector<vector<int>> prevs(N);
  REP(i, N) if (!seen[i]) {
    for (int v = i; indegree[v] == 0; v = next[v]) {
      seen[v] = true;
      --indegree[next[v]];
      prevs[next[v]].push_back(v);
    }
  }

  vector<int> cycle;  // declared outside the loop so I can reuse the memory

  // Vertices in the cycle are assigned consecutive indexes 0 to cycle.size()
  // (exclusive). It doesn't matter which vertex is the start (with index 0),
  // so long as they are numbered consecutively, so the distance between
  // vertices v and w in the cycle can be computed as:
  // (cycle_index[w] - cycle_index[v] + cycle.size()) % cycle.size()
  vector<int> cycle_index(N, -1);
  // dist_to_cycle[w] = d if vertex w is `d` steps removed from the current
  // cycle. Note that dist_to_cycle always contains exactly `d` entries, its
  // values are the distinct numbers between 1 and `d` (inclusive), and its
  // keys are the vertices on the path from the cycle entry to `v`, with
  // dist_to_cycle[v] = d (if d > 0).
  vector<int> dist_to_cycle(N, -1);

  REP(i, N) if (!seen[i]) {
    // Identify a new cycle starting at `i`
    int v = i, idx = 0;
    cycle.clear();
    do {
      cycle_index[v] = idx++;
      seen[v] = true;
      cycle.push_back(v);
      v = next[v];
    } while (v != i);

    // For each vertex in the cycle, visit the tree of vertices leading to the
    // cycle at this vertex.
    REP(entry_index, cycle.size()) {
      int v = cycle[entry_index];  // current vertex; initially the cycle vertex
      int d = 0;  // current distance to the cycle
      for (;;) {
        // Answer queries which have the source vertex as the current node.
        for (Query *q : queries_by_source[v]) {
          if (int e = dist_to_cycle[q->b]; e != -1) {
            // Destination lies on the path towards the cycle (not on the cycle itself)
            q->answer = d - e;
          } else if (int j = cycle_index[q->b]; j != -1) {
            // Destination lies on the cycle, which is `d` steps away.
            q->answer = d + (j - entry_index + cycle.size()) % cycle.size();
          } else {
            // Destination is not reachable.
            q->answer = -1;
          }
        }

        // Find the next tree vertex to visit. This effectively does a pre-order
        // traversal of the tree connected to the initial cycle vertex, while
        // maintaining the invariants that `d` is the current distance from `v`
        // to the cycle (i.e., the distance to the root of the tree) and
        // dist_to_cycle contains the distances of the vertices on the path from
        // `v` to the cycle vertex.
        while (d > 0 && prevs[v].empty()) {
          dist_to_cycle[v] = -1;
          --d;
          v = next[v];
        }
        if (prevs[v].empty()) {
          break;
        }
        int w = prevs[v].back();
        prevs[v].pop_back();
        v = w;
        dist_to_cycle[v] = ++d;
      }
    }

    for (int v : cycle) cycle_index[v] = -1;
  }

  for (const Query &q : queries) cout << q.answer << '\n';
}
