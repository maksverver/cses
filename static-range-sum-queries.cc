// Static Range Sum Queries
// https://cses.fi/problemset/task/1646
//
// Solution: Fenwick array
//
// See also dynamic-range-sum-queries.cc

#include <bits/stdc++.h>

#include "fenwick.h"

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int64_t> A(N);
  for (auto &x : A) cin >> x;

  fenwick_construct(A);

  while (Q--) {
    int a = 0, b = 0;
    cin >> a >> b;
    cout << fenwick_rangesum(A, a - 1, b) << '\n';
  }
}
