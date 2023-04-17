// Counting Tilings
// https://cses.fi/problemset/task/2181
//
// Memory-optimized version of counting-tilings.cc

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

constexpr int MAX_W = 10;
constexpr int MOD = 1e9 + 7;

int H, W;

int memo[2][MAX_W][1 << MAX_W];

int Calc(int r, int c, unsigned blocked) {
  if (c == W) return Calc(r + 1, 0, blocked);
  if (r == H) return 1;
  int &m = memo[r&1][c][blocked];
  if (m >= 0) return m;
  if (blocked & (1 << c)) return m = Calc(r, c + 1, blocked & ~(1 << c));
  int res = 0;
  if (r + 1 < H) res += Calc(r, c + 1, blocked | (1 << c));  // vertical tile
  if (c + 1 < W && !(blocked & (3 << c))) res += Calc(r, c + 2, blocked); // horizontal tile
  res %= MOD;
  return m = res;
}

}  // namespace

int main() {
  memset(memo, -1, sizeof(memo));
  cin >> W >> H;
  assert(W <= MAX_W);

  memset(memo, -1, sizeof(memo));
  for (int r = H - 1; r >= 0; --r) {
    memset(memo[r&1], -1, sizeof(memo[r&1]));
    for (int c = W - 1; c >= 0; --c) {
      for (unsigned blocked = 0; blocked != (1u << W); ++blocked) {
        Calc(r, c, blocked);
      }
    }
  }

  cout << memo[0][0][0] << endl;
}
