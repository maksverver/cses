// Distinct Numbers
// https://cses.fi/problemset/task/1621

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (int &i : A) cin >> i;
  std::sort(A.begin(), A.end());
  int count = 0;
  REP(i, N) if (i == 0 || A[i - 1] != A[i]) ++count;
  cout << count << endl;
}
