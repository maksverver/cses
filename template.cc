#include <bits/stdc++.h>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class S, class T> ostream& operator<<(ostream &os, const pair<S, T> &p) {
  return os << '{' << p.first << ',' << p.second << '}';
}

template<class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) os << (i ? " " : "") << v[i];
  return os;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  int answer = -1;
  cout << answer << '\n';
}
