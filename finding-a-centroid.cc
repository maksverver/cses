// Finding a Centroid
// https://cses.fi/problemset/task/2079
//
// Problem:
//
// You are given a tree on N vertices. A centroid is a vertex `v` such that all
// child subtrees of v have size less than or equal to N/2.
//
// It follows that a tree has either 1 or 2 centroids (in the latter case, the
// 2 centroids are connected by an edge, and they have equal subtree sizes N/2).
//
// Solution:
//
// To find the centroid we can start at an arbitrary vertex v. Consider all
// child subtrees w. If there is a child w whose subtree has size > N/2, then
// by definition v is not a centroid, and the centroid must lie in the subtree
// rooted at w. Logically, there can be at most 1 child subtree with size > N/2.
// If there is no such child then `v` is a centroid, by definition.
//
// (The second centroid, if there is one, would be the child w with subtree size
// exactly equal to N/2. But for this problem, we only have to identify one
// centroid.)
//
// So we can just pick an arbitrary vertex and walk the edges towards the
// largest child subtrees until we find the centroid. We'll examine each
// bidirectional edge at most twice. If we memoize the SubtreeSize() function,
// the algorithm has O(N) time and O(N) space complexity.

#include <bits/stdc++.h>

using namespace std;

static unordered_map<int64_t, int> memo;

static int N;
static vector<vector<int>> adj;

int SubtreeSize(int v, int par) {
  int64_t key = int64_t{N} * v + par;
  auto it = memo.find(key);
  if (it != memo.end()) return it->second;
  int res = 1;
  for (int w : adj[v]) if (w != par) res += SubtreeSize(w, v);
  return memo[key] = res;
}

int FindCentroid() {
  int v = 0;
repeat:
  for (int w : adj[v]) {
    if (SubtreeSize(w, v) > N / 2) {
      v = w;
      goto repeat;
    }
  }
  return v;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  cin >> N;
  adj = vector<vector<int>>(N);
  for (int e = 0; e < N - 1; ++e) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  cout << FindCentroid() + 1 << '\n';
}
