// Subarray Sum Queries
// https://cses.fi/problemset/task/1190
//
// Solution:
//
// Use a segment tree with a custom data type and combining function.
//
// Similar to prefix-sum-queries.cc.

#include <bits/stdc++.h>

#include "segment-tree.h"

using namespace std;

struct Datum {
  int64_t sum;
  int64_t max_prefix_sum;
  int64_t max_suffix_sum;
  int64_t max_subarray_sum;

  static Datum single(int v) {
    return Datum{v, max(v, 0), max(v, 0), max(v, 0)};
  }
};

static Datum Combine(const Datum &a, const Datum &b) {
  return Datum{
    .sum=a.sum + b.sum,
    .max_prefix_sum=max(a.max_prefix_sum, a.sum + b.max_prefix_sum),
    .max_suffix_sum=max(b.max_suffix_sum, b.sum + a.max_suffix_sum),
    .max_subarray_sum=max(a.max_suffix_sum + b.max_prefix_sum,
      max(a.max_subarray_sum, b.max_subarray_sum))};
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<Datum> A(N);
  for (int i = 0; i < N; ++i) {
    int a = 0;
    cin >> a;
    A[i] = Datum::single(a);
  }

  SegmentTree tree(A, Datum::single(0), Combine);

  while (M--) {
    int i = 0, v = 0;
    cin >> i >> v;
    tree.Set(i - 1, Datum::single(v));
    cout << tree.GetRange(0, N).max_subarray_sum << '\n';
  }
}
