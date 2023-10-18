// Counting Divisors
// https://cses.fi/problemset/task/1713
//
// By the fundamental theorem of arithmetic, each integer x can be expressed
// uniquely as a product of primes: x = p^a × q^b × r^c × ... (where p, q, r,
// etc. are primes, and a, b, c, etc. are nonnegative integers).
//
// The divisors of x are the numbers y = p^a' × q^b' x r^c' × ... where
// 0 ≤ a' ≤ a, 0 ≤ b' ≤ b, 0 ≤ c' ≤ c, etc. That is, each subset of the prime
// factors has a distinct product that is logically a divisor of x, since:
// x = y × (p^(a - 'a) × q(b - b') × r(c - c') × ...)
//
// So to count divisors, we only need to calculate the multiplicity of prime
// factors (the values of a, b, c, etc.) and then we can calculate the number
// of divisors as (a + 1) × (b + 1) × (c + 1) ...

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  while (N-- > 0) {
    int x = 0;
    cin >> x;
    int answer = 1;
    for (int d = 2; d*d <= x; ++d) {
      int n = 0;
      while (x % d == 0) x /= d, ++n;
      answer *= n + 1;
    }
    if (x > 1) answer *= 2;
    cout << answer << '\n';
  }
}
