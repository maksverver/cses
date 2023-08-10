// Dynamic Range Minimum Queries
// https://cses.fi/problemset/task/1649
//
// Solution: segment tree.

#include <bits/stdc++.h>

#include "segment-tree.h"

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  auto min = [](int64_t a, int64_t b) { return a < b ? a : b; };
  int64_t max_value = std::numeric_limits<int64_t>::max();
  SegmentTree tree(N, max_value, min);

  for (int i = 0; i < N; ++i) {
    int x = 0;
    cin >> x;
    tree.Set(i, x);
  }

  while (Q--) {
    int t = 0;
    cin >> t;
    if (t == 1) {
      int i = 0, x = 0;
      cin >> i >> x;
      --i;
      tree.Set(i, x);
    }
    if (t == 2) {
      size_t i = 0, j = 0;
      cin >> i >> j;
      --i;
      assert(i < j && j <= N);

      cout << tree.GetRange(i, j) << '\n';
    }
  }
}
