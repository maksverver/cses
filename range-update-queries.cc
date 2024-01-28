// Range Update Queries
// https://cses.fi/problemset/task/1651
//
// Problem:
//
// We are given an initial array and a list of queries, each of which either
// asks to print the value at a position, or to add a value to each element in a
// subarray.
//
// Solution:
//
// Use a lazy segment tree to store the contents of the array.

#include <bits/stdc++.h>

#include "lazy-segment-tree.h"

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  LazySegmentTree<int64_t> tree(A);
  while (Q--) {
    int type = 0;
    cin >> type;
    if (type == 1) {
      int i = 0, j = 0, v = 0;
      cin >> i >> j >> v;
      tree.AddRange(i - 1, j, v);
    } else {
      assert(type == 2);
      int i = 0;
      cin >> i;
      cout << tree.Get(i - 1) << '\n';
    }
  }
}
