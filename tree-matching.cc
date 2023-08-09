// Tree Matching
// https://cses.fi/problemset/task/1130

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

static vector<vector<int>> adj;

// Returns a pair: maximum matching if `v` is matched to parent, and maximum if
// `v` is not matched to parent. If `v` is matched, then we must match the child
// subtrees independently. If `v` is unmatched, then we can match it to one
// child; we choose the child that gives the maximum improvement (which is at
// most 1).
pair<int, int> Calc(int v, int par) {
  int base = 0, extra = 0;
  for (int w : adj[v]) if (w != par) {
    auto [x, y] = Calc(w, v);
    assert(x >= y);
    base += y;
    extra = max(extra, x - y);
  }
  assert(extra == 0 || extra == 1);
  return {base + 1, base + extra};
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  adj = vector<vector<int>>(N);
  REP(i, N - 1) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  cout << Calc(0, 0).second << '\n';
}
