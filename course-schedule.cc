// Course Schedule
// https://cses.fi/problemset/task/1679
//
// Solution: standard topological sort.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> prerequisites(N + 1);
  vector<vector<int>> required_by(N + 1);
  for (int m = 0; m < M; ++m) {
    int a = 0, b = 0;
    cin >> a >> b;

    prerequisites[b]++;
    required_by[a].push_back(b);
  }

  vector<int> order;
  for (int i = 1; i <= N; ++i) {
    if (prerequisites[i] == 0) order.push_back(i);
  }
  for (size_t i = 0; i < order.size(); ++i) {
    int a = order[i];
    for (int b : required_by[a]) {
      if (--prerequisites[b] == 0) order.push_back(b);
    }
  }

  if (order.size() < N) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    for (size_t i = 0; i < order.size(); ++i) {
      if (i > 0) cout << ' ';
      cout << order[i];
    }
    cout << endl;
  }
}
