// Knight's Tour
// https://cses.fi/problemset/task/1689
//
// Despite the misleading name, the problem is actually to find a Hamiltonian
// path (not a cycle!) on a chessboard using only knight's moves starting from
// a given square.
//
// My solution: use a depth-first search, where I explore squares that have the
// lowest remaining outdegree first. This is called Warndorf's rule:
// https://en.wikipedia.org/wiki/Knight%27s_tour#Warnsdorff's_rule
//
// Another potentional solution would involve finding a single tour. This can
// then be hardcoded, and a tour starting from any square can be found by
// starting from that square and then following the cycle.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

const int DR[8] = { -2, -2, -1, -1, +1, +1, +2, +2 };
const int DC[8] = { -1, +1, -2, +2, -2, +2, -1, +1 };

static int visited[8][8];

bool Reachable(int r, int c) {
  return 0 <= r && r < 8 && 0 <= c && c < 8 && visited[r][c] == 0;
}

int CountMovesFrom(int r, int c) {
  int count = 0;
  for (int d = 0; d < 8; ++d) if (Reachable(r + DR[d], c + DC[d])) ++count;
  return count;
}

struct Option {
  int r, c, moves_from;
};

ostream &operator<<(ostream &os, const Option &o) {
  return os << "Option{" << o.r << ',' << o.c << ',' << o.moves_from << "}";
}

bool Dfs(int r, int c, int depth) {
  visited[r][c] = depth;
  if (depth == 64) return true;

  Option options[8];
  int noption = 0;
  REP(d, 8) {
    int r2 = r + DR[d];
    int c2 = c + DC[d];
    if (Reachable(r2, c2)) {
      options[noption++] = Option{r2, c2, CountMovesFrom(r2, c2)};
    }
  }

  std::sort(&options[0], &options[noption], [](const Option &a, const Option &b){
    return a.moves_from < b.moves_from;
  });

  REP(i, noption) {
    if (Dfs(options[i].r, options[i].c, depth + 1)) return true;
  }

  visited[r][c] = 0;
  return false;
}

int main() {
  int r = 0, c = 0;
  cin >> c >> r;

  bool solved = Dfs(r - 1, c - 1, 1);
  assert(solved);

  REP(r, 8) {
    REP(c, 8) {
      if (c > 0) cout << ' ';
      cout << visited[r][c];
    }
    cout << '\n';
  }
}
