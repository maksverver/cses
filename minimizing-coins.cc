// Minimizing Coins
// https://cses.fi/problemset/task/1634/
//
// f(0) = 0
// f(x) = min f(x - c) for c in C

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

constexpr int inf = 999'999'999;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> C(N);
  for (auto &c : C) cin >> c;
  std::sort(C.begin(), C.end());
  C.erase(std::unique(C.begin(), C.end()), C.end());

  vector<int> min_coins(X + 1, inf);
  min_coins[0] = 0;
  for (int i = 1; i <= X; ++i) {
    for (int c : C) {
      if (c > i) break;
      min_coins[i] = min(min_coins[i], min_coins[i - c] + 1);
    }
  }

  cout << (min_coins[X] == inf ? -1 : min_coins[X]) << '\n';
}
