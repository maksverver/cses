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

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

/* Converts a regular array into a Fenwick array (in linear time). */
void fenwick_construct(std::vector<int64_t> &a) {
  for (size_t i = 1; i < a.size(); i = 2 * i)
    for (size_t j = 2 * i - 1; j < a.size(); j += 2 * i)
      a[j] += a[j - i];
}

/* Calculates the sum of the first `n` elements in `a` (which are the elements
   with zero-based indices strictly less than n). */
int64_t fenwick_prefixsum(const std::vector<int64_t> &a, size_t n) {
  int64_t res = 0;
  while (n > 0) res += a[n - 1], n &= n - 1;
  return res;
}

/* Calculates the sum of elements from index i to j (exclusive). */
int64_t fenwick_rangesum(const std::vector<int64_t> &a, size_t i, size_t j) {
  return i < j ? fenwick_prefixsum(a, j) - fenwick_prefixsum(a, i) : 0;
}

/* Adds `v` to the value stored at index `i`. */
void fenwick_update(std::vector<int64_t> &a, size_t i, int v) {
  while (i < a.size()) a[i] += v, i |= i + 1;
}

/* Retrieves the value stored at index `i`. */
int64_t fenwick_retrieve(const std::vector<int64_t> &a, size_t i) {
  int64_t res = a[i];
  for (size_t bit = 1; i & bit; bit += bit) res -= a[i ^ bit];
  return res;
}

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
