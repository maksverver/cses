// Coin Combinations II
// https://cses.fi/problemset/task/1636
//
// f(0, 0) = 1
// f(i, j) = f(i - 1, j) + f(i - 1, j - C[i])

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> C(N);
  for (auto &c : C) cin >> c;

  vector<int> combis(X + 1);
  combis[0] = 1;
  for (int c : C) {
    for (int i = c; i <= X; ++i) {
      combis[i] = (combis[i] + combis[i - c]) % 1'000'000'007;
    }
  }

  cout << combis[X] << '\n';
}
