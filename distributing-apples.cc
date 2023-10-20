// Distributing Apples
// https://cses.fi/problemset/task/1716
//
// https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)

#include "mod-int.h"

#include <bits/stdc++.h>

using namespace std;

using MI = ModInt<int32_t, int64_t, (int32_t)(1e9 + 7)>;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;

  vector<MI> fac = {1};
  while (fac.size() <= N - 1 + M) fac.push_back(fac.back() * fac.size());

  cout << fac[N - 1 + M] / fac[N - 1] / fac[M] << '\n';
}
