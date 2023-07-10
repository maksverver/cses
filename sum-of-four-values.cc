// Sum of Four Values
// https://cses.fi/problemset/task/1642
//
// Fun! See also: Sum of Two Values, Sum of Three Values
//
// The solution below runs in O(N^2).

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int64_t> A(N);
  for (int64_t &a : A) cin >> a;

  // Invariant: sums contains an entry {A[i] + A[j], {i, j}} for each i < j < k.
  unordered_map<int64_t, pair<int, int>> sums;
  for (int k = 0; k < N; ++k) {
    for (int l = k + 1; l < N; ++l) {
      int half = A[k] - A[l];
      if (auto it = sums.find(X - half); it != sums.end()) {
        auto [i, j] = it->second;
        cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << ' ' << l + 1 << endl;
        return 0;
      }
    }
    for (int j = 0; j < k; ++j) {
      sums[A[j] + A[k]] = {j, k};
    }
  }

  cout << "IMPOSSIBLE" << endl;
}
