// https://cses.fi/problemset/task/1133

#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

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

int N;
vector<vector<int>> adj;

// subtree_size[v] = size of subtree rooted at v, but excluding the path
// to the top. For example:
//
//      1        |
//     / \       |
//    2   3      |
//   / \         |
//  4   5        |
//
// subtree_size[1] = 5
// subtree_size[2] = 3
// subtree_size[4] = 1
vector<int64_t> subtree_size;

// subtree_acc[v] = sum of distances to nodes in the subtree rooted at v
vector<int64_t> subtree_acc;

// acc[v] = sum of dist(v, w) for all w
vector<int64_t> acc;

std::pair<int64_t, int64_t> CalcSubtreeSize(int v, int u) {
  int64_t size = 1;
  int64_t acc = 0;
  for (int w : adj[v]) if (w != u) {
    auto [s, a] = CalcSubtreeSize(w, v);
    size += s;
    acc += a + s;
  }
  subtree_size[v] = size;
  subtree_acc[v] = acc;
  return {size, acc};
}

void CalcAcc(int v, int u, int64_t parent_size, int64_t parent_acc) {
  int64_t my_acc = subtree_acc[v] + parent_acc + parent_size;
  int64_t my_size = subtree_size[v] + parent_size;
  acc[v] = my_acc;
  for (int w : adj[v]) if (w != u) {
    CalcAcc(w, v, my_size - subtree_size[w], my_acc - subtree_acc[w] - subtree_size[w]);
  }
}

vector<int64_t> Solve() {
  subtree_size = vector<int64_t>(N);
  subtree_acc = vector<int64_t>(N);
  acc = vector<int64_t>(N);
  CalcSubtreeSize(0, 0);
  CalcAcc(0, 0, 0, 0);
  return acc;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  N = 0;
  cin >> N;
  adj = vector<vector<int>>(N);
  REP(n, N - 1) {
    int u = 0, v = 0;
    cin >> u >> v;
    --u, --v;
    assert(u != v && 0 <= u && u < N && 0 <= v && v < N);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << Solve() << '\n';
}
