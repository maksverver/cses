// Book Shop
// https://cses.fi/problemset/task/1158
//
// C=cost of book, S=pages in book
//
// f(books, total price)
// f(0, 0)=0
// f(i, j)=max(f(i - 1, j - C[i]) + S[i], f(i - 1, j))

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> C(N), S(N);
  for (auto &c : C) cin >> c;
  for (auto &s : S) cin >> s;

  vector<int> dp(X + 1);
  for (int i = 0; i < N; ++i) {
    for (int j = X; j >= C[i]; --j) {
      dp[j] = max(dp[j], dp[j - C[i]] + S[i]);
    }
  }
  cout << dp[X] << endl;
}
