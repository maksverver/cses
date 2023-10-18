// Common Divisors
// https://cses.fi/problemset/task/1081
//
// Problem: given an array of integers A, find a pair of elements x, y in A
// such that gcd(x, y) is maximal.
//
// Solution: for each integer x, enumerate the divisors in O(sqrt x) time, by
// testing divisors from 1 to sqrt(x) inclusive: if x is divisible by d
// (1 ≤ d ≤ sqrt(x)), then both d and x/d are divisors of x (but avoid
// overcounting in the case where x == d*d, which means d = x/d).
//
// Complexity: O(N × sqrt(max A))

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int answer = 0;
  std::bitset<1000001> divisors;
  auto add_divisor = [&](int d) {
    if (divisors.test(d)) answer = max(answer, d); else divisors.set(d);
  };

  int N = 0;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int x = 0;
    cin >> x;
    for (int d = 1; d*d <= x; ++d) if (x % d == 0) {
      add_divisor(d);
      if (d*d < x) add_divisor(x / d);
    }
  }
  cout << answer << '\n';
}
