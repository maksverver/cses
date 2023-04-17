// Counting Tilings
// https://cses.fi/problemset/task/2181
//
// Classic dynamic programming: count domino tilings.
//
// See Calc() for the logic. We will place blocks from top to bottom and from
// left right. For each free space we place either a horizontal (2x1) or
// vertical (1x2) piece. That means we know that all positions before the
// current one are already covered, and we only need to keep track of the next
// W spaces. Example:
//
//         c
//     ########
//  r: ####@bbb
//     aaaa....
//
// Positions marked '#' are guaranteed to be covered, positions marked '.' are
// guaranteed to be empty. We can represent the state as a bitmask of size W,
// to create an O(H × W × 2^W) solution, which works since H ≤ 1000 and W ≤ 10.
//
// See also counting-tilings-2.cc

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

constexpr int MAX_W = 10;
constexpr int MOD = 1e9 + 7;

int H, W;

// It should be possible to calculate this using O(W × 2^W) space instead of O(W × H × 2^W)
int memo[MAX_W][1000][1 << MAX_W];

int Calc(int r, int c, unsigned blocked) {
  if (c == W) {
    return Calc(r + 1, 0, blocked);
  }
  if (r == H) {
    assert(blocked == 0);
    return 1;
  }
  int &m = memo[c][r][blocked];
  if (m >= 0) return m;
  if (blocked & (1 << c)) {
    return m = Calc(r, c + 1, blocked & ~(1 << c));
  }
  int res = 0;
  if (r + 1 < H) {
    // Vertical tile.
    res += Calc(r, c + 1, blocked | (1 << c));
  }
  if (c + 1 < W && !(blocked & (3 << c))) {
    // Horizontal tile.
    res += Calc(r, c + 2, blocked);
  }
  res %= MOD;
  return m = res;
}

}  // namespace

int main() {
  memset(memo, -1, sizeof(memo));
  cin >> W >> H;
  assert(W <= MAX_W);
  cout << Calc(0, 0, 0) << endl;
}
