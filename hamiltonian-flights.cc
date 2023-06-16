// Hamiltonian Flights
// https://cses.fi/problemset/task/1690
//
// Problem:
//
// Given a directed graph on N vertices (N ≤ 20), count the number of
// Hamiltonian paths from vertex 1 to N.
//
// Solution:
//
// Recursion with memoization (dynamic programming).

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

constexpr int MOD = 1e9 + 7;

int V, E;
vector<vector<int>> adj;

// Note: we only need to memoize 19 cities, not 20, because when we reach the
// last city, we return immediately. It's also possible to use 1<<18 instead of
// 1<<19 space per city, because the `v`-th bit of `visited` is always set, so
// we could remove it from the bitmask, but implementing this is not worth the
// effort.
int memo[19][1 << 19];

int Solve(int v, unsigned visited) {
  if (v == V - 1) return visited == (1u << V) - 1;

  int &m = memo[v][visited];
  if (m != -1) return m;

  int res = 0;
  for (int w: adj[v]) if ((visited & (1u << w)) == 0) {
    res = (res + Solve(w, visited | (1u << w))) % MOD;
  }
  return m = res;
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  cin >> V >> E;
  adj.resize(V);
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
  }

  REP(v, V - 1) REP(m, 1 << (V - 1)) memo[v][m] = -1;
  cout << Solve(0, 1) << '\n';
}
