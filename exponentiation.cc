// Exponentiation
// https://cses.fi/problemset/task/1095
//
// Solution: exponentiation by squaring.

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1000000007;

int32_t ModPow(int32_t a, int32_t b) {
  int c = 1;
  for (; b > 0; b >>= 1) {
    if (b & 1) c = (int64_t) c * a % MOD;
    a = (int64_t) a * a % MOD;
  }
  return c;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  while (N--) {
    int32_t a = 0, b = 0;
    cin >> a >> b;
    cout << ModPow(a, b) << '\n';
  }
}
