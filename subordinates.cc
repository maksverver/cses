// Subordinates
// https://cses.fi/problemset/task/1674/

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) os << (i ? " " : "") << v[i];
  return os;
}

static int N;
static vector<vector<int>> reports;
static vector<int> subordinates;

int CalcSubordinates(int i) {
  int res = 0;
  for (int j : reports[i]) res += CalcSubordinates(j) + 1;
  return subordinates[i] = res;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  cin >> N;
  reports = vector<vector<int>>(N);
  subordinates = vector<int>(N);
  FOR(i, 1, N) {
    int p = 0;
    cin >> p;
    reports[p - 1].push_back(i);
  }
  CalcSubordinates(0);
  cout << subordinates << '\n';
}
