#include <bits/stdc++.h>

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

void SolveCase() {
  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (int &i : A) cin >> i;
  cout << -1 << '\n';
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  if (N == 1) {
    cout << "1" << endl;
  } else if (N == 2 || N == 3) {
    cout << "NO SOLUTION" << endl;
  } else if (N == 4) {
    cout << "3 1 4 2" << endl;
  } else {
    // Interleave numbers:
    //  N=5: 1 4 2 5 3
    //  N=6: 1 4 2 5 3 6
    //  N=10: 1 6 2 7 3 8 4 9 5 10
    // etc.
    vector<int> P(N);
    REP(i, N) P[i] = i % 2 == 0 ? i/2 + 1: (N + 1) / 2 + i/2 + 1;
    cout << P << endl;
  }
}
