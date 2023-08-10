// Company Queries I
// https://cses.fi/problemset/task/1687

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  int layers = 1;
  while ((1 << (layers - 1)) < N) ++layers;

  // ancestors[l][i] is the 2^l-th ancestor of i.
  vector<vector<int>> ancestors(layers, vector<int>(N + 1));
  for (int i = 2; i <= N; ++i) {
    cin >> ancestors[0][i];
  }
  for (int l = 1; l < layers; ++l) {
    for (int i = 1; i <= N; ++i) {
      ancestors[l][i] = ancestors[l - 1][ancestors[l - 1][i]];
    }
  }

  auto nth_ancestor = [&ancestors](int v, int n) {
    for (int l = 0; v > 0 && n > 0; ++l, n >>= 1) {
      if (n & 1) v = ancestors[l][v];
    }
    return v;
  };

  while (Q-- > 0) {
    int x = 0, k = 0;
    cin >> x >> k;
    int a = nth_ancestor(x, k);
    cout << (a > 0 ? a : -1) << '\n';
  }
}
