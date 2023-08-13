// Subtree Queries
// https://cses.fi/problemset/task/1137
//
// Solution:
//
// If we relabel the vertices in the input according to the pre-order traversal
// of the tree, then each subtree corresponds with a consecutive range of
// integers. Example:
//
//                0 [0..4]      |
//               / \            |
//       [1..3] 1   4 [4..4]    |
//             / \              |
//     [2..2] 2   3 [3..3]      |
//
// Now we can store the values in a Fenwick array, and querying the sum of
// values is simply a range sum query.
//
// Complexity: O(N + Q + Q log N) time and O(N) space.
//
// See also path-queries.cc for a twist on the same idea!

#include "fenwick.h"

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

vector<vector<int>> adj;
vector<int> begin;
vector<int> end;

static void Dfs(int v, int par, int &id) {
  begin[v] = id++;
  for (int w : adj[v]) if (w != par) Dfs(w, v, id);
  end[v] = id;
}

void Solve() {
  // Read input.
  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (int &a : A) cin >> a;
  adj = vector<vector<int>>(N);
  REP(_, N - 1) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  // Pre-order traversal to calculate begin/end indices.
  int id = 0;
  begin = vector<int>(N);
  end = vector<int>(N);
  Dfs(0, -1, id);
  assert(id == N);

  // Initialize Fenwick array with values associated with vertices.
  vector<int64_t> B(N);
  REP(v, N) B[begin[v]] = A[v];
  fenwick_construct(B);

  // Process queries.
  REP(_, Q) {
    int type = 0, v = 0;
    cin >> type >> v;
    --v;
    if (type == 1) {
      int x = 0;
      cin >> x;
      fenwick_update(B, begin[v], x - fenwick_retrieve(B, begin[v]));
    } else {
      assert(type == 2);
      cout << fenwick_rangesum(B, begin[v], end[v]) << '\n';
    }
  }
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  Solve();
}
