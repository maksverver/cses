// Binomial Coefficients
// https://cses.fi/problemset/task/1079

#include "mod-int.h"

#include <bits/stdc++.h>

using namespace std;

using MI = ModInt<int32_t, int64_t, (int32_t)(1e9 + 7)>;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  vector<MI> fac = {1};
  int N = 0;
  cin >> N;
  while (N-- > 0) {
    int a = 0, b = 0;
    cin >> a >> b;
    assert(0 <= b && b <= a);
    while (fac.size() <= a) fac.push_back(fac.back() * fac.size());
    cout << fac[a] / (fac[b] * fac[a - b]) << '\n';
  }
}
