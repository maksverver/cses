// Money Sums
// https://cses.fi/problemset/task/1745
//
// Standard subset sum problem.
//
// f(coin index, total):
//
// f(i, 0) = true
// f(i, x) = f(i - 1, x) or f(i - 1, x - A[i])
//
// Note we can implement everything in a single array to save memory, but we
// need to iterate from right to left, to avoid reusing the same coin.

#include <bits/stdc++.h>
#include <numeric>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  int total = accumulate(A.begin(), A.end(), 0);
  vector<char> can(total + 1);
  can[0] = true;
  for (int a : A) {
    for (int i = total; i >= a; --i) {
      if (can[i - a]) can[i] = true;
    }
  }

  int count = accumulate(can.begin() + 1, can.end(), 0);
  cout << count << '\n';
  bool first = true;
  for (int i = 1; i <= total; ++i) if (can[i]) {
    if (first) first = false; else cout << ' ';
    cout << i;
  }
  cout << '\n';
}
