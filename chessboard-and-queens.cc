// Chessboard and Queens
// https://cses.fi/problemset/task/1624
//
// Problem: count the number of ways you can place eight queens on a chessboard
// without attacking each other, and without placing a queen on a reserved space
// given in the input.
//
// This is a variation of the classic eight-queens problem.
//
// Solution: recursion with backtracking. We place queens in columns from left
// to right, keeping track of which rows and diagonals are already covered.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

char blocked[8][8];

constexpr int Diag1(int r, int c) { return r + c; }
constexpr int Diag2(int r, int c) { return r + 7 - c; }
constexpr unsigned Bit(int i) { return 1u << i; }

int64_t Search(int c, unsigned row_mask, unsigned d1_mask, unsigned d2_mask) {
  if (c == 8) return 1;
  int64_t res = 0;
  REP(r, 8) {
    if (blocked[r][c]) continue;
    if (row_mask & Bit(r)) continue;
    int d1 = Diag1(r, c);
    if (d1_mask & Bit(d1)) continue;
    int d2 = Diag2(r, c);
    if (d2_mask & Bit(d2)) continue;
    res += Search(c + 1, row_mask | Bit(r), d1_mask | Bit(d1), d2_mask | Bit(d2));
  }
  return res;
}

}  // namespace

int main() {
  REP(i, 8) {
    std::string row;
    cin >> row;
    assert(row.size() == 8);
    REP(j, 8) blocked[i][j] = row[j] == '*';
  }

  cout << Search(0, 0, 0, 0) << endl;
}
