// Coin Combinations I
// https://cses.fi/problemset/task/1635
//
// f(-x) = 0
// f(0) = 1
// f(n) = sum f(n - c) for c in C

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
  for (int i = 1; i <= X; ++i) {
    for (int c : C) if (c <= i) {
      combis[i] = (combis[i] + combis[i - c]) % 1'000'000'007;
    }
  }

  cout << combis[X] << '\n';
}
