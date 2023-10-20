// Christmas Party
// https://cses.fi/problemset/task/1717
//
// Problem: count the the number of permutations P of length n such that P_i ≠ i
// for all i.
//
// Solution:
//
// Let C_n be the answer for length n. Clearly:
//
//  C_0 = 1 [] (empty permutation)
//  C_1 = 0 (no solution possible)
//  C_2 = 1 [2 1]
//  C_3 = 2 [2 3 1], [3 1 2]
//
// etc.
//
// We can defined C_n = (n - 1)×(C_{n-1} + C_{n-2}).
//
// Logic:
//
// Consider the valid permutations of length n - 1. These can be represented as
// a list of cycles (by definition, all cycles have length > 1). We can extend
// those permutations to length n by inserting the element n in any of these
// cycles in exactly n - 1 ways. Example: for n=3, we have 2 permutations
// ([2 3 1] and [3 1 2]) which can be extended to 6 permutations ([2 3 4 1],
// [4 3 1 2], [2 4 1 3], [3 4 2 1], [3 1 4 2], and [4 1 2 3]). This accounts for
// (n - 1)×C_{n-1} new permutations.
//
// However, we can also create a new 2-cycle in (n - 1) ways. (P_n = i, P_i = n,
// for 1 ≤ i < n). The remaining (n - 2) elements can be permuted in C_{n - 2}
// ways. This accounts for the other (n - 2)×C_{n-2} permutations.
//
// See also:
//  - https://en.wikipedia.org/wiki/Derangement
//  - https://en.wikipedia.org/wiki/Rencontres_numbers

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;

  int a = 1, b = 0;
  for (int n = 2; n <= N; ++n) {
    int c = (long long) (a + b) * (n - 1) % MOD;
    a = b;
    b = c;
  }
  cout << b << '\n';
}
