// Monsters
// https://cses.fi/problemset/task/1194
//
// Solution:
//
// Two breadth-first searches (BFS): one from the monsters (to find the earliest
// time they can be at any cell) and then a second from the player (to see if
// they can get to the edge of the grid without running into any monsters).

#include <bits/stdc++.h>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

static pair<int, int> DIRS[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
static char DIR_LABELS[4] = {'U', 'L', 'R', 'D'};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int H = 0, W = 0;
  cin >> H >> W;
  vector<string> M(H);
  for (auto &row : M) cin >> row;

  const int inf = H * W + 1;

  vector<vector<int>> monster_dist(H, vector<int>(W, inf));
  vector<vector<int>> human_dist(H, vector<int>(W, inf));
  vector<vector<int>> last_dir(H, vector<int>(W, -1));
  deque<pair<int, int>> todo;

  // BFS pass 1: find distance to nearest monster.
  REP(r, H) REP(c, W) if (M[r][c] == 'M') {
    monster_dist[r][c] = 0;
    todo.push_back({r, c});
  }
  while (!todo.empty()) {
    auto [r, c] = todo.front();
    todo.pop_front();
    for (auto [dr, dc] : DIRS) {
      int r2 = r + dr, c2 = c + dc;
      if (r2 < 0 || r2 >= H || c2 < 0 || c2 >= W || M[r2][c2] == '#') continue;

      if (monster_dist[r2][c2] == inf) {
        monster_dist[r2][c2] = monster_dist[r][c] + 1;
        todo.push_back({r2, c2});
      }
    }
  }

  // BFS pass 2: find path to edge, avoiding monsters
  REP(r, H) REP(c, W) if (M[r][c] == 'A') {
    human_dist[r][c] = 0;
    todo.push_back({r, c});
  }
  while (!todo.empty()) {
    auto [r, c] = todo.front();
    todo.pop_front();
    if (r == 0 || r == H - 1 || c == 0 || c == W - 1) {
      // Solution found! Reconstruct path.
      std::string path;
      for (int dir = last_dir[r][c]; dir != -1; dir = last_dir[r][c]) {
        path += DIR_LABELS[dir];
        auto [dr, dc] = DIRS[dir];
        r -= dr, c -= dc;
      }
      std::reverse(path.begin(), path.end());
      cout << "YES\n" << path.size() << '\n' << path << '\n';
      return 0;
    }
    REP(dir, 4) {
      auto [dr, dc] = DIRS[dir];
      int r2 = r + dr, c2 = c + dc;
      if (M[r2][c2] != '#' && monster_dist[r2][c2] > human_dist[r][c] + 1 && human_dist[r2][c2] == inf) {
        human_dist[r2][c2] = human_dist[r][c] + 1;
        last_dir[r2][c2] = dir;
        todo.push_back({r2, c2});
      }
    }
  }

  cout << "NO\n";
}
