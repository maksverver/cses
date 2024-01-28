// Tree Diameter
// https://cses.fi/problemset/task/1131

#include <bits/stdc++.h>

using namespace std;

namespace {

int N;
vector<vector<int>> adj;

// subtree_depth[v] = depth of subtree rooted at v, but excluding the path
// to the top. For example:
//
//      1        |
//     / \       |
//    2   3      |
//   / \         |
//  4   5        |
//
// subtree_depth[1] = 2
// subtree_depth[2] = 1
// subtree_depth[4] = 0
vector<int> subtree_depth;

// depth[v] = depth of tree rooted at v
//
// In the above example:
//  depth[1] = 2
//  depth[2] = 2
//  depth[4] = 3
vector<int> depth;

int CalcSubtreeDepth(int v, int u) {
  int res = 0;
  for (int w : adj[v]) if (w != u) res = std::max(res, 1 + CalcSubtreeDepth(w, v));
  subtree_depth[v] = res;
  return res;
}

// Calculate depth of subtree rooted at 'v', coming from parent `u`.
// `d` is the maximum length of the path going up to the parent.
//
// The idea is that if we call two children with the deepest subtrees
// w1 and w2, with depths d1 >= d2.
//
//           (u)
//            | d
//           (v)
//       d1 / | \ d2
//       (w1) |  (w2)
//           (w)
//
void CalcDepth(int v, int u, int d) {
  int w1 = -1, d1 = 0, d2 = 0;
  for (int w : adj[v]) if (w != u) {
    int d = subtree_depth[w] + 1;
    if (d > d1) {
      d2 = d1;
      w1 = w;
      d1 = d;
    } else if (d > d2) {
      d2 = d;
    }
  }
  depth[v] = std::max(d, d1);
  for (int w : adj[v]) if (w != u) {
    // Note the new value of `d` is the longest path going either up
    // (w-v-u-...) or (w-v-w1-...) or, if w == w1, (w-v-w2-....)
    CalcDepth(w, v, std::max(d, w1 == w ? d2 : d1) + 1);
  }
}

int Solve() {
  subtree_depth = vector<int>(N);
  depth = vector<int>(N);
  CalcSubtreeDepth(0, 0);
  CalcDepth(0, 0, 0);

  return *max_element(depth.begin(), depth.end());
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  N = 0;
  cin >> N;
  adj = vector<vector<int>>(N);
  for (int e = 0; e < N - 1; ++e) {
    int u = 0, v = 0;
    cin >> u >> v;
    --u, --v;
    assert(u != v && 0 <= u && u < N && 0 <= v && v < N);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << Solve() << '\n';
}
