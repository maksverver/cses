// Divisor Analysis
// https://cses.fi/problemset/result/7439308/
//
// Given a number X = product of p_i^k_i (i ≤ 1 ≤ n).
//
// We need to calculate:
//
//  1. The number of divisors.
//  2. The sum of divisors.
//  3. The product of divisors.
//
// First, define x_i as the product of the first i terms in the input, i.e.:
//
//   x_0 = 1
//   x_i = x_{i-1} × p_i^k_i
//
// Consider the set of divisors D_i whose elements are divisors of x_i.
// Then we have:
//
//   D_0 = {1}
//   D_i = { d × p_i^j for d in D_{i-1} and 0 ≤ j ≤ k_i }
//
// In other words, we can calculate the sets of divisors by multiplying the
// previous divisors by each of the values of 1, p_i, p_i^2, .. , p_i^k_i.
// These are all distinct, so |D_i| = |D_{i-1}| × k_i.
//
// We will not calculate these sets explicitly, but use the definition to
// calculate the answers using dynamic programming.
//
// Now we can define num_i, the number of divisors of x_i = |D_i|, as follows:
//
//   num_0 = 1
//   num_i = num_{i-1} + (k_i + 1)
//
// The total number of divisors num_n is effectively the sum of (k_i + 1).
//
// We can define sum_i, the sum of divisors of x_i, as follows:
//
//   sum_0 = 1
//   sum_i =
//     sum(d × p_i^j for d in D_{i-1} and 0 ≤ j ≤ k_i) =
//     sum(sum_{i-1} × p_i^j for 0 ≤ j ≤ k_i) =
//     sum_{i-1} × sum(p_i^j for 0 ≤ j ≤ k_i)
//
// The above contains the sum of a prefix of a geometric series which
// has a closed-form solution:
//
//   sum(p^0 + p^1 + p^2 + .. + p^k) = p^(n + 1) - 1 / (p - 1)
//
// This requires calculating the modular inverse of (p - 1), which should exist
// because p is a prime, so either p = 2 and (p - 1) = 1 and the inverse is 1,
// or p is odd, so p - 1 is even, and therefore coprime with 10000000007.
//
// Alternatively, we can calculate recursively, using similar logic as
// exponentiation by squaring:
//
//   sum(p^0 + p^1 + p^2 + .. + p^2n) =
//     sum(p^0 + p^1 + p^2 + .. + p^(2n - 1)) + p^2n
//
//   sum(p^0 + p^1 + p^2 + .. + p^(2n - 1)) =
//     sum(p^0 + p^1 + p^2 + .. + p^(n - 1)) × (1 + p^n)
//
//   sum(p^0 + p^1 + p^2 + .. + p^(2n - 1)) =
//     sum(p^0 + p^1 + p^2 + .. + p^(n - 1)) +
//     p^n × sum(p^0 + p^1 + p^2 + .. + p^(n - 1))
//
// Both of these approaches take O(log n) time.
//
// Finally, we can define prod_i, the product of divisors of x_i, using:
//
//   prod_0 = 1
//   prod_i =
//     product(d × p_i^j for d in D_{i-1} and 0 ≤ j ≤ k_i) =
//     product(d for d in D_{i-1}) ^ (k_i + 1) ×
//       product(p_i^j for 0 ≤ j ≤ k_i) ^ |D_{i-1}| =
//    prod_{i_1} ^ (k_i + 1) × (p_i^((k_i + 1)×(k_i) / 2)) ^ num_{i-1} =
//       prod_{i_1} ^ (k_i + 1) × (p_i^((k_i + 1)×(k_i) / 2 × num_{i-1}))
//
// The above uses:
//
//   product(p^i for 0 ≤ i ≤ k) = p^0 × p^1 × p^2 × .. × p^n
//       = p^(0 + 1 + 2 + .. + n) = p^((n + 1) × n / 2)
//
// Which we can calculate efficiently using exponentiation by squaring.
//
// All the calculations are done modulo 1,000,000,007.
//
// To be able to exponentiate by num_i efficiently, we need to calculate num_i
// modulo (MOD - 1), since by by Fermat's little theorem, if x is coprime to p,
// then x^(p - 1) = 1 modulo p. In other words:
//
//    pow(x, p) % MOD == pow(x, p % (MOD - 1)) % MOD.

#include <iostream>

#define int long long

constexpr int MOD = 1e9 + 7;

// Calculates x^e in O(log e) time using exponentiation by squaring.
static int Pow(int x, int e) {
  int r = 1;
  while (e > 0) {
    if (e & 1) r = r * x % MOD;
    x = x * x % MOD;
    e >>= 1;
  }
  return r;
}

// Returns 1 + p + p^2 + p^3 + .. + p^(n - 1)
static int SumOfPowers(int p, int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  if (n % 2 == 1) return (Pow(p, n - 1) + SumOfPowers(p, n - 1)) % MOD;
  return (1 + Pow(p, n / 2)) * SumOfPowers(p, n / 2) % MOD;
}

signed main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);

  int N = 0;
  std::cin >> N;
  int count = 1, sum = 1, product = 1, n = 1;
  while (N-- > 0) {
    int p = 0, k = 0;
    std::cin >> p >> k;

    count = count * (k + 1) % MOD;
    sum = sum * SumOfPowers(p, k + 1) % MOD;
    product = Pow(product, k + 1) * Pow(Pow(p, (k + 1) * k / 2), n) % MOD;
    n = n * (k + 1) % (MOD - 1);
  }
  std::cout << count << ' ' << sum << ' ' << product << std::endl;
}
