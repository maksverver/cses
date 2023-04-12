// Collecting Numbers
// https://cses.fi/problemset/task/2216
//
// Insight: since we need to collect numbers in order, we need to start a new
// round whenever the index of the next number is lower than the previous one.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<pair<int, int>> A(N);
  REP(i, N) cin >> A[i].first, A[i].second = i;

  sort(A.begin(), A.end());

  int rounds = 0;
  int last_i = N;
  for (auto [v, i] : A) {
    if (i < last_i) ++rounds;
    last_i = i;
  }
  cout << rounds << endl;
}
