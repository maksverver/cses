// Dice Combinations
// https://cses.fi/problemset/task/1633
//
// f(-x) = 0
// f(0)  = 1
// f(n)  = f(n - 1) + f(n - 2) + .. + f(n - 6)

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  // A[i] is the number of ways to roll a total of `i`.
  vector<int> A(N + 1);
  A[0] = 1;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= 6 && j <= i; ++j) {
      A[i] = (A[i] + A[i - j]) % 1'000'000'007;
    }
  }
  cout << A[N] << endl;
}
