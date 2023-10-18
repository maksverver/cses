// Sum of Divisors
// https://cses.fi/problemset/task/1082
//
// Problem:
//
// Given integer N (1 ≤ N ≤ 10^12) calculate the sum of the divisors
// of integers in range [1..N].
//
// Solution:
//
// The naive solution would be to calculate the sum of divisors for each number
// in range and them sum them together, but that would be much too slow: around
// O(N log N) at the least. Instead, we will look at each divisor separately.
//
// For a given divisor d, we know there are exactly floor(N/d) integers in
// range that have d as a divisor: [d, 2d, 3d, 4d, .. N], so we can add
// floor(N/d)×d to the sum. However, doing this for all divisors from 1 to N
// would still take too long!
//
// We can optimize it from O(N) to O(sqrt N) using the fact that if an integer
// x is divisible by d, it is also divisible by x/d, so we only need to consider
// divisors up to sqrt(N) (inclusive). To avoid double-counting, we should
// only consider values x/d > d, which means values of x in range
// [d(d + 1), d(d + 2), d(d + 3), .. N], and the sum of the divisors x/d
// is the sum of [d + 1, d + 2, d + 3, .. N/d].
//
// However, there is one problem! Doing this naively, we would still overcount.
// For example, x=20 has divisor 5, which can be found when d=4 (20/4 = 5) and
// when d=5, so we add 5 to the sum twice. There is a simple solution: when
// counting divisor d, we know that for all values x < d^2, the divisor d
// has already been accounted for as x/e for some value of e < d. So instead
// of counting d as a divisor of multiples of d in range [1..N], we should
// count the multiples of d in range [d^2+1..N]. Note that this range contains
// the values [d(d + 1), d(d + 2), d(d + 3), .. N], which is exactly the same
// range as before, but this time we are interested only in the length rather
// than the sum.
//
// Note: this logic seems similar to the Sieve of Eratosthenes.

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int answer = 0;
  int64_t N = 0;
  cin >> N;
  for (int64_t d = 1; d * d <= N; ++d) {
    // k = number of integers in range [d^2..N] that are divisible by d:
    int64_t k = (N - d*d + d)/d % MOD;

    // Sum of divisors d
    int64_t a = k * d;

    // Sum of divisors x/d where x in range [d^2+d..N]
    //
    // This is the sum of [d*(d + 1), d*(d + 2), d*(d + 3), ... N]/d =
    // sum of [d + 1, d + 2, d + 3, .. N/d] which has length l = k - 1,
    // (uses the formula for triangular numbers)
    int64_t b = (k - 1)*(d + 1) + (k - 1)*(k - 2) / 2;

    answer = (answer + a + b) % MOD;
  }
  answer = (answer + MOD) % MOD;  // ensure answer is nonnegative
  cout << answer << '\n';
}
