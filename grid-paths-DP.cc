// Grid Paths
// https://cses.fi/problemset/task/1638
//
// f(0, 0) = 1
// f(i, j) = 0 if grid[i, j] = '*' else f(i - 1, j) + f(i, j - 1)

#include <bits/stdc++.h>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) {
    if (i > 0) os << ' ';
    os << v[i];
  }
  return os;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<string> M(N);
  for (auto &s : M) cin >> s;

  vector<vector<int>> count(N, vector<int>(N));
  REP(i, N) REP(j, N) if (M[i][j] != '*') {
    count[i][j] = (i == 0 && j == 0) ? 1 :
        ((i > 0 ? count[i - 1][j] : 0) + (j > 0 ? count[i][j - 1] : 0)) % 1'000'000'007;
  }
  cout << count[N - 1][N - 1] << '\n';
}
