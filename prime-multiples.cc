// Prime Multiples
// https://cses.fi/problemset/task/2185
//
// Inclusion-exclusion.

#include <bits/stdc++.h>

using namespace std;

#define int int64_t

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

signed main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, K = 0;
  cin >> N >> K;
  vector<int> A(K);
  for (auto &a : A) cin >> a;

  int answer = 0;
  FOR(m, 1, 1 << K) {
    int n = -N;
    REP(i, K) if (m & (1 << i)) n /= -A[i];
    answer += n;
  }
  cout << answer << '\n';
}
