// Pizzeria Queries
// https://cses.fi/problemset/task/2206
//
// Solution:
//
// Let A[i] be the price in building i. Then the minimum cost at building j is
// the minimum of P[i] - i + j for 0 ≤ i ≤ j and P[i] + i - j for j ≤ i < N.
//
// We can store the values of `A[i] - i` in one segment tree, and the values of
// `A[i] + i` in another segment tree, and then we can calculate the cost in
// O(log N) time, for an O(N + Q log N) time solution.

#include <bits/stdc++.h>

#include "segment-tree.h"

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<int> V1(N);
  vector<int> V2(N);
  REP(i, N) V1[i] = A[i] - i;
  REP(i, N) V2[i] = A[i] + i;

  auto min = [](int a, int b) { return std::min(a, b); };
  SegmentTree<int, decltype(min)> tree1(V1, std::numeric_limits<int>::min(), min);
  SegmentTree<int, decltype(min)> tree2(V2, std::numeric_limits<int>::min(), min);

  REP(q, Q) {
    int type = 0, i = 0;
    cin >> type >> i;
    --i;
    if (type == 1) {
      int x = 0;
      cin >> x;
      tree1.Set(i, x - i);
      tree2.Set(i, x + i);
    } else {
      assert(type == 2);
      cout << min(tree1.GetRange(0, i + 1) + i, tree2.GetRange(i, N) - i) << '\n';
    }
  }
}
