// Trailing Zeros
// https://cses.fi/problemset/task/1618
//
// Given N, calculate how many trailing zeroes are in the factorial of N.
//
// Logic: the factorial of N is defined as 1 × 2 × 3 × .. × N.
//
// By the prime number theorem, any number including N! can be written as a
// product of primes, e.g. N! = 2^a + 3^b + 5^c + ... etc. Since trailing zeros
// in a decimal number correspond with divisibility by 10 = 2 × 5, the number of
// trailing zeroes in the decimal representation of N! is equal to min(a, c).
// It can be shown easily that a <= b <= c <= .. etc., so it suffices to count
// just c, the total number of prime factors 5 across all terms in the product.
//
// For a given N, the number of terms 1..N that have at least one prime factor
// 5 is equal to floor(N/5) (i.e., for N=100, it's 5, 10, 15, .., 95, 100, or
// 20 total). The number of terms that have at least two prime factors 5 is
// equal to floor(N/25) (i.e., for N=100, it's 25, 50, 75, 100, or 4 total),
// but since we already counted the first factor, we should only add 1 more.
// We can continue this with increasing powers of 5. For N=100, we stop because
// 5^3 = 125 > 100, so there are 0 terms that are divisible by 125.
//
// So 100! will have 20 + 4 = 24 trailing zeros.

#include <bits/stdc++.h>

using namespace std;

int main() {
  int N = 0;
  cin >> N;

  int answer = 0;
  for (int64_t div = 5; div <= N; div *= 5) {
    answer += N / div;
  }
  cout << answer << endl;
}
