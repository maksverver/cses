// Game Routes
// https://cses.fi/problemset/task/1681
//
// Topological sorting.

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> num_incoming(N + 1);
  vector<vector<int>> incoming(N + 1);
  vector<vector<int>> outgoing(N + 1);
  for (int m = 0; m < M; ++m) {
    int a = 0, b = 0;
    cin >> a >> b;
    num_incoming[b]++;
    incoming[b].push_back(a);
    outgoing[a].push_back(b);
  }

  vector<int> num_ways(N + 1, 0);
  vector<int> order;
  for (int i = 1; i <= N; ++i) {
    if (num_incoming[i] == 0) order.push_back(i);
  }
  num_ways[1] = 1;
  for (size_t i = 0; i < order.size(); ++i) {
    int b = order[i];
    for (int a : incoming[b]) num_ways[b] = (num_ways[b] + num_ways[a]) % MOD;
    for (int c : outgoing[b]) if (--num_incoming[c] == 0) order.push_back(c);
  }
  cout << num_ways[N] << endl;
}
