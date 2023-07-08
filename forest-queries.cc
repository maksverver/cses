// Forest Queries
// https://cses.fi/problemset/task/1652
//
// Solution: inclusion-exclusion.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  vector<vector<int>> A(N, vector<int>(N));

  REP(i, N) {
    string row;
    cin >> row;
    assert(row.size() == N);
    REP(j, N) A[i][j] = row[j] == '*';
  }

  // C[n][m] = sum i=0..n-1, j=0..m-1 A[i][j]
  vector<vector<int>> C(N + 1, vector<int>(N + 1));
  REP(i, N) REP(j, N) C[i + 1][j + 1] = C[i][j + 1] + C[i + 1][j] - C[i][j] + A[i][j];

  REP(q, Q) {
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    cin >> r1 >> c1 >> r2 >> c2;
    --r1, --c1;
    assert(r1 < r2);
    assert(c1 < c2);
    int answer = C[r2][c2] - C[r2][c1] - C[r1][c2] + C[r1][c1];
    cout << answer << '\n';
  }
}
