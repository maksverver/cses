// Prefix Sum Queries
// https://cses.fi/problemset/task/2166
//
// Fun problem!
//
// Solution:
//
// Use a segment tree with a custom data type and combining function.
//
// We can calculate the maximum prefix sum of a subarray from the total sum
// and maximum prefix sum of two halves of the subarray. See Datum and Combine()
// defined below for details.
//
// See also subarray-sum-queries.cc which is a similar idea.

#include <bits/stdc++.h>

#include "segment-tree.h"

using namespace std;

struct Datum {
  int64_t sum;
  int64_t max_prefix_sum;

  static Datum single(int v) { return Datum{v, v > 0 ? v : 0};  }
};

static Datum Combine(const Datum &a, const Datum &b) {
  return Datum{
    .sum=a.sum + b.sum,
    .max_prefix_sum=max(a.max_prefix_sum, a.sum + b.max_prefix_sum)};
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<Datum> A(N);
  for (int i = 0; i < N; ++i) {
    int a = 0;
    cin >> a;
    A[i] = Datum::single(a);
  }

  SegmentTree tree(A, Datum::single(0), Combine);

  while (Q--) {
    int type = 0, a = 0, b = 0;
    cin >> type >> a >> b;
    --a;
    if (type == 1) {
      tree.Set(a, Datum::single(b));
    } else {
      assert(type == 2);
      std::cout << tree.GetRange(a, b).max_prefix_sum << '\n';
    }
  }
}
