// Grid Paths
// https://cses.fi/problemset/task/1625
//
// The clue is in the problem statement: ”There are 88418 paths in a 7×7 grid.”
// That means the total number of paths is fairly small; if we can enumerate all
// paths efficiently, we can easily filter them down to match the given pattern.
//
// Solution: recursion with backtracking and pruning.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

constexpr std::array<pair<int, int>, 4> DIRS = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

constexpr int H = 7;
constexpr int W = 7;
constexpr int start_row = 0;
constexpr int start_col = 0;
constexpr int finish_row = 6;
constexpr int finish_col = 0;

// Input pattern.
std::string pattern;

// Marks cells visited during our search. Updated by Enter()/Leave().
char visited[H][W];

// Counts number of unvisited neighbors per cell. Updated by Enter()/Leave().
char neighbors[H][W];

constexpr bool InRange(int r, int c) { return 0 <= r && r < H && 0 <= c && c < W; }
constexpr bool IsFinish(int r, int c) { return r == finish_row && c == finish_col; }

constexpr int GetDir(char ch) {
  if (ch == 'U') return 0;
  if (ch == 'L') return 1;
  if (ch == 'R') return 2;
  if (ch == 'D') return 3;
  assert(ch == '?');
  return -1;
}

void Enter(int r, int c) {
  assert(!visited[r][c]);
  visited[r][c] = true;
  for (auto [dr, dc] : DIRS) if (InRange(r + dr, c + dc)) --neighbors[r + dr][c + dc];
}

void Leave(int r, int c) {
  assert(visited[r][c]);
  visited[r][c] = false;
  for (auto [dr, dc] : DIRS) if (InRange(r + dr, c + dc)) ++neighbors[r + dr][c + dc];
}

constexpr pair<int, int> Step(int r, int c, int dir) {
  auto [dr, dc] = DIRS[dir];
  return {r + dr, c + dc};
}

int64_t Search(int r, int c, int pos) {
  if (pos == H*W - 1) {
    return IsFinish(r, c) ? 1 : 0;
  }

  Enter(r, c);

  int64_t res = 0;

  // Check if the direction is fixed by the pattern string.
  int must_pick_dir = GetDir(pattern[pos]);

  // Search our neighbors for cells with only 1 unvisited neighbor (excluding
  // the final destination): if there is one, we MUST visit it now, because we
  // will not be able to return to it later.
  //
  // For example, in the following configuration, we must go right, otherwise
  // we create a dead end that we cannot visit without getting stuck.
  //
  //   ####        ####
  //   #@.#        ##.#  impossible!
  //   #..#        #@.#
  //
  // Note that this is our main pruning logic. Without it, the solution is still
  // correct, but it would run much slower!
  REP(d, DIRS.size()) {
    auto [r2, c2] = Step(r, c, d);
    if (InRange(r2, c2) && !visited[r2][c2] && !IsFinish(r2, c2)) {
      if (neighbors[r2][c2] == 0) goto pruned;
      if (neighbors[r2][c2] == 1) {
        if (must_pick_dir != -1 && must_pick_dir != d) goto pruned;
        must_pick_dir = d;
      }
    }
  }

  // Now either move in the single direction we can move in, or try out all
  // four possible directions.
  REP(d, 4) if (must_pick_dir == -1 || must_pick_dir == d) {
    auto [r2, c2] = Step(r, c, d);
    if (InRange(r2, c2) && !visited[r2][c2]) res += Search(r2, c2, pos + 1);
  }

pruned:
  Leave(r, c);
  return res;
}

}  // namespace

int main() {
  // Initialize neighbor count.
  REP(r, H) REP(c, W) for (auto [dr, dc] : DIRS) if (InRange(r + dr, c + dc)) ++neighbors[r][c];

 cin >> pattern;
 assert(pattern.size() == H*W - 1);

  cout << Search(0, 0, 0) << endl;
}
