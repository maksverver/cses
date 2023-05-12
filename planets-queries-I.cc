// Planets Queries I
// https://cses.fi/problemset/task/1750
//
// Fun problem! Precompute the destination for numbers of steps that are powers
// of 2. Then every query can be solved in O(log K) time. Overall, the runtime
// is O((N + Q) log (max K)).

#include <bits/stdc++.h>

using namespace std;

// Smallest exponent such that 2**max_exp > any value of K.
constexpr int max_exp = 30;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  // next[d][x] == planet reached from x after taking 2**d steps
  vector<vector<int>> next(max_exp, vector<int>(N + 1));
  for (int i = 1; i <= N; ++i) {
    cin >> next[0][i];
  }

  // Precompute next[d][x] for all values of d (0 < d < max_exp)
  for (int d = 1; d < max_exp; ++d) {
    for (int x = 1; x <= N; ++x) {
      next[d][x] = next[d - 1][next[d - 1][x]];
    }
  }

  // Process queryies.
  for (int q = 0; q < Q; ++q) {
    int x = 0, k = 0;
    cin >> x >> k;

    assert(k < (1 << max_exp));
    for (int d = max_exp - 1; d >= 0; --d) {
      if (k >= (1 << d)) {
        x = next[d][x];
        k -= 1 << d;
      }
    }
    cout << x << '\n';
  }
}
