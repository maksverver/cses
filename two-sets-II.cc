// Two Sets
// https://cses.fi/problemset/task/1093
//
// Variant on a subset sum problem.
//
// The sum of numbers 1..N is N * (N + 1) / 2. The number of partitions with
// equal sum is equal to the number of ways to make a single subset equal to
// half that sum, which means a solution is only possible if the sum of digits
// is even.
//
// At this point it's basically a subset sum problem, and we can implement it
// the same as in e.g. money-sums.cc.
//
// f(sum, max) = the number of ways to make a sum with distinct integers between 1..max
// f(0, 0) = 1
// f(s, 0) = 0                                (s > 0)
// f(s, m) = f(s, m - 1)                      (m > s)
// f(s, m) = f(s, m - 1) + f(s - m, m - 1)    (m ≤ s)
//
// Two optimizations:
//
//  - We only need to keep the last row of the matrix (see also money-sums.cc)
//  - If we were to calculate f(total/2, N) we would double-count all solutions
//    (since every pair of sets can be swapped). Instead of dividing by 2 in the
//    end, we can just compute f(total/2, N-1) instead, effectively forcing N
//    to always be in the "other" set.

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int Solve(int N) {
  int total = N * (N + 1) / 2;
  if (total % 2 != 0) return 0;
  int half = total / 2;

  vector<int> m(half + 1);
  m[0] = 1;
  for (int max = 1; max < N; ++max) {
    for (int sum = half; sum >= max; --sum) {
      m[sum] += m[sum - max];
      m[sum] %= MOD;
    }
  }
  return m[half];
}

int main() {
  int N = 0;
  cin >> N;
  cout << Solve(N) << endl;
}
