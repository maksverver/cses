// School Dance
// https://cses.fi/problemset/task/1696
//
// Classical bipartite matching problem. Can be solved using Ford-Fulkerson.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(v) ((v).size())

namespace {

vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<char> visited;

static bool match(int i) {
  if (visited[i]) return false;
  visited[i] = true;
  for (int j : adj[i]) {
    if (matchR[j] < 0 || match(matchR[j])) {
      matchL[i] = j;
      matchR[j] = i;
      return true;
    }
  }
  return false;
}

static bool match_one() {
  REP(i, SZ(adj)) if (matchL[i] < 0 && match(i)) return true;
  return false;
}

static int maximum_matching() {
  int res = 0;
  matchL.assign(SZ(adj), -1);
  matchR.assign(SZ(adj), -1);
  while (visited.assign(SZ(adj), 0), match_one()) ++res;
  return res;
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, M = 0, K = 0;
  cin >> N >> M >> K;
  adj.resize(N + M);
  REP(_, K) {
    int v = 0, w = 0;
    cin >> v >> w;
    --v, --w;
    adj[v].push_back(N + w);
  }
  cout << maximum_matching() << '\n';
  REP(v, N) if (int w = matchL[v]; w != -1) {
    cout << v + 1 << ' ' << w - N + 1 << '\n';
  }
}
