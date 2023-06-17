// Static Range Minimum Queries
// https://cses.fi/problemset/task/1647
//
// Solution: ad-hoc segment tree

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<vector<int64_t>> layers;
  layers.push_back(vector<int64_t>(N));
  for (auto &x : layers[0]) cin >> x;

  while (layers.back().size() > 1) {
    const vector<int64_t> &prev_layer = layers.back();
    vector<int64_t> next_layer;
    for (size_t i = 0; i + 2 <= prev_layer.size(); i += 2) {
      next_layer.push_back(min(prev_layer[i], prev_layer[i + 1]));
    }
    layers.push_back(next_layer);
  }

  while (Q--) {
    size_t i = 0, j = 0;
    cin >> i >> j;
    --i;
    assert(i < j && j <= N);

    int64_t answer = 1e18;
    for (const vector<int64_t> &layer : layers) {
      if (i&1) answer = min(answer, layer[i++]);
      if (j&1) answer = min(answer, layer[--j]);
      i >>= 1;
      j >>= 1;
      if (i == j) break;  // tiny optimization
    }
    assert(i == j);

    cout << answer << '\n';
  }
}
