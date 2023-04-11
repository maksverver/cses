#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

void SolveCase() {
  int64_t x = 0, y = 0;
  cin >> y >> x;
  int64_t z = std::max(x, y);
  cout << (z - 1)*(z - 1) + (z % 2 == 0 ? (x == z ? y : 2*z - x) : (y == z ? x : 2*z - y)) << '\n';
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int T = 0;
  cin >> T;
  REP(t, T) SolveCase();
}
