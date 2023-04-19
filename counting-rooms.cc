// Counting Rooms
// https://cses.fi/problemset/task/1192
//
// Classic breadth-first search (BFS) or flood fill.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int H = 0, W = 0;
  cin >> H >> W;
  vector<string> M(H);
  for (auto &row : M) cin >> row;

  vector<vector<char>> seen(H, vector<char>(W, false));
  int rooms = 0;
  deque<pair<int, int>> todo;
  REP(r, H) REP(c, W) if (M[r][c] == '.' && !seen[r][c]) {
    ++rooms;
    todo.push_back({r, c});
    while (!todo.empty()) {
      auto [r, c] = todo.front();
      todo.pop_front();
      pair<int, int> adjacent[4] = {{r + 1, c}, {r, c + 1}, {r - 1, c}, {r, c - 1}};
      for (auto [r2, c2] : adjacent) {
        if (0 <= r2 && r2 < H && 0 <= c2 && c2 < W && M[r2][c2] == '.' && !seen[r2][c2]) {
          seen[r2][c2] = true;
          todo.push_back({r2, c2});
        }
      }
    }
  }
  cout << rooms << endl;
}
