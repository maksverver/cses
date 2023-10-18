// Exponentiation II
// https://cses.fi/problemset/task/1712
//
// Solution: Fermat's little theorem implies a^(p - 1) % p = 1, so we can
// compute a^b^c % p as a^(b^c % (p - 1)) % p.

#include <bits/stdc++.h>

using namespace std;

int32_t ModPow(int32_t a, int32_t b, int32_t mod) {
  int c = 1;
  for (; b > 0; b >>= 1) {
    if (b & 1) c = (int64_t) c * a % mod;
    a = (int64_t) a * a % mod;
  }
  return c;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  while (N-- ) {
    int32_t a = 0, b = 0, c =0;
    cin >> a >> b >> c;
    cout << ModPow(a, ModPow(b, c, 1e9+6), 1e9+7) << '\n';
  }
}
