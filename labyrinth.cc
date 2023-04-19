// Labyrinth
// https://cses.fi/problemset/task/1193
//
// Classic breadth-first search (BFS) or flood fill.
//
// Only tricky part is reconstructing the path to the destination.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

static int DR[4] = { -1,  0,  0, 1 };
static int DC[4] = {  0, -1, +1, 0 };

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int H = 0, W = 0;
  cin >> H >> W;
  vector<string> M(H);
  for (auto &row : M) cin >> row;

  vector<vector<int>> prev(H, vector<int>(W, -1));
  deque<pair<int, int>> todo;
  REP(r, H) REP(c, W) if (M[r][c] == 'A') todo.push_back({r, c});
  while (!todo.empty()) {
    auto [r, c] = todo.front();
    todo.pop_front();

    REP(d, 4) {
      int r2 = r + DR[d], c2 = c + DC[d];
      if (0 <= r2 && r2 < H && 0 <= c2 && c2 < W && prev[r2][c2] == -1) {
        if (M[r2][c2] == '.') {
          prev[r2][c2] = d;
          todo.push_back({r2, c2});
        } else if (M[r2][c2] == 'B') {
          // Destination reached! Reconstruct path.
          string solution;
          int r = r2, c = c2;
          while (M[r][c] != 'A') {
            solution += "ULRD"[d];
            r -= DR[d], c -= DC[d];
            d = prev[r][c];
          }
          reverse(solution.begin(), solution.end());
          cout << "YES\n" << solution.size() << '\n' << solution << '\n';
          return 0;
        }
      }
    }
  }

  cout << "NO\n";
}
