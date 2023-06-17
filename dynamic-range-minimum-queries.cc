// Dynamic Range Minimum Queries
// https://cses.fi/problemset/task/1649
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
    int t = 0;
    cin >> t;
    if (t == 1) {
      int i = 0, x = 0;
      cin >> i >> x;
      --i;

      // Set A[i] to x
      layers[0][i] = x;
      for (size_t layer = 1; layer < layers.size(); ++layer) {
        i >>= 1;
        if (i >= layers[layer].size()) break;
        layers[layer][i] = min(layers[layer - 1][2*i], layers[layer - 1][2*i + 1]);
      }
    }
    if (t == 2) {
      size_t i = 0, j = 0;
      cin >> i >> j;
      --i;
      assert(i < j && j <= N);

      // Query minimum of A[i..j)
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
}
