// Removing Digits
// https://cses.fi/problemset/task/1637
//
// f(0) = 0
// f(x) = min f(x - d) where d is a digit of x

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i) {
    A[i] = 999'999'999;
    int x = i;
    while (x > 0) {
      if (x % 10 <= i) A[i] = std::min(A[i], A[i - x % 10] + 1);
      x /= 10;
    }
  }

  cout << A[N] << '\n';
}
