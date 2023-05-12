// Planets Queries II
// https://cses.fi/problemset/task/1160
//
// Fun problem!
//
// The graph consists of multiple simple cycles, which each vertex in the cycle
// having a tree attached of nodes that are not part of the cycle.
//
// There is a path from v to w only if:
//
//  1. v and w lie on the same cycle
//  2. v lies on the subtree that leads to a cycle vertex u,
//     and w lies on the same cycle as u
//  3. v is a descendant of w in the tree that connects to the cycle.
//
// For example:
//
//   1 --> 2 --> 3 <-- 6 <-- 7
//         ^     |     ^            <---
//         |     v     |           9   10 <-- 11
//         5 <-- 4     8            --->
//
// Here, we can see each of the three cases:
//
//   1. 2 is reachable from 4 (in 2 steps)
//   2. 5 is reachable from 1 via cycle vertex 2 (in 1 + 3 = 4 steps)
//   3. 6 is reachable from 7 (in 1 step)
//
// So what we can do is identify the subtrees, then the cycles.
// Then for each cycle vertex, we can traverse the attached subtree
// in-order, keeping track of the vertices that lie on the cycle and the
// path towards the current vertex.
//
// The above test case is covered by planets-queries-II-test.in.
//
// Time complexity: O((N + Q) log N)

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
  REP(i, N) if (!seen[i]) {
    // Identify a new cycle starting at `i`
    map<int, int> cycle_index;
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
      // dist_to_cycle[w] = d if vertex w is `d` steps removed from the current
      // cycle. Note that dist_to_cycle always contains exactly `d` entries, its
      // values are the distinct numbers between 1 and `d` (inclusive), and its
      // keys are the vertices on the path from the cycle entry to `v`, with
      // dist_to_cycle[v] = d (if d > 0).
      map<int, int> dist_to_cycle;
      for (;;) {
        // Answer queries which have the source vertex as the current node.
        for (Query *q : queries_by_source[v]) {
          if (auto it = dist_to_cycle.find(q->b); it != dist_to_cycle.end()) {
            // Destination lies on the path towards the cycle (not on the cycle itself)
            q->answer = d - it->second;
          } else if (auto it = cycle_index.find(q->b); it != cycle_index.end()) {
            // Destination lies on the cycle, which is `d` steps away.
            q->answer = d + (it->second - entry_index + cycle.size()) % cycle.size();
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
          dist_to_cycle.erase(v);
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
  }

  for (const Query &q : queries) cout << q.answer << '\n';
}
