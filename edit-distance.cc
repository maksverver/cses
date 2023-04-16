// Edit Distance
// https://cses.fi/problemset/task/1639
//
// Classic Levenshtein distance.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  string S, T;
  cin >> S >> T;

  // dist[i][j] == distance between S[0..i) and S[0..j)
  vector<vector<int>> dist(S.size() + 1, vector<int>(T.size() + 1));
  for (int i = 1; i <= S.size(); ++i) dist[i][0] = i;
  for (int j = 1; j <= T.size(); ++j) dist[0][j] = j;

  for (int i = 1; i <= S.size(); ++i) {
    for (int j = 1; j <= T.size(); ++j) {
      dist[i][j] = S[i - 1] == T[j - 1] ? dist[i - 1][j - 1] :
          1 + std::min(dist[i - 1][j - 1], std::min(dist[i][j - 1], dist[i - 1][j]));
    }
  }
  cout << dist[S.size()][T.size()] << '\n';
}
