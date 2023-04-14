// Josephus Problem I
// https://cses.fi/problemset/task/2162
//
// Basically, use a linked list to track people.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  int N = 0;
  cin >> N;

  vector<int> next(N);
  REP(i, N - 1) next[i] = i + 1;

  int pos = 0;
  REP(n, N) {
    if (n > 0) cout << ' ';
    cout << next[pos] + 1;
    pos = next[pos] = next[next[pos]];
  }
  cout << '\n';
}
