// Distinct Colors
// https://cses.fi/problemset/task/1139
//
// Fun! This is a combination of the techniques from subtree-queries.cc and
// distinct-values-queries-2.cc. See those solutions for details.

#include "fenwick.h"

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) os << (i ? " " : "") << v[i];
  return os;
}

namespace {

vector<vector<int>> adj;
vector<int> begin;
vector<int> end;

void Dfs(int v, int par, int &id) {
  begin[v] = id++;
  for (int w : adj[v]) if (w != par) Dfs(w, v, id);
  end[v] = id;
}

void Solve() {
  // Read input.
  int N = 0;
  cin >> N;
  vector<int> C(N);
  for (int &c : C) cin >> c;
  adj = vector<vector<int>>(N);
  REP(_, N - 1) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(w);
    adj[w].push_back(v);
  }

  // Pre-order traversal to calculate begin/end indices.
  int id = 0;
  begin = vector<int>(N);
  end = vector<int>(N);
  Dfs(0, -1, id);
  assert(id == N);

  // Note that `begin` indices are distinct, so they form a permutation 0..N-1.
  // This is the inverse permutation: inv_begin[i] == v such that begin[j] = v.
  vector<int> inv_begin(N, -1);
  REP(i, N) inv_begin[begin[i]] = i;

  vector<int> answers(N);

  unordered_map<int, int> last_position;
  vector<int> distinct(N);
  for (int i = N - 1; i >= 0; --i) {
    int v = inv_begin[i];
    int &last_pos = last_position[C[v]];
    if (last_pos > 0) fenwick_update(distinct, last_pos, -1);
    last_pos = i;
    fenwick_update(distinct, last_pos, +1);
    answers[v] = fenwick_prefixsum(distinct, end[v]);
  }

  cout << answers << endl;
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  Solve();
}
