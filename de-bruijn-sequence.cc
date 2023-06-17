// De Bruijn Sequence
// https://cses.fi/problemset/task/1692
//
// A de Bruijn sequence of order N over an alphabet A is a string that contains
// all possible substrings of length N.
//
// If we allow wrap-around, then there is a sequence of length |A|^N, which is
// optimal since there are |A|^N different substrings of length N, each of which
// start at a different position.
//
// When wrap-around is not allowed, then we have to copy the first (N - 1)
// elements at the end of the cycle, which again, is optimal.
//
// For example, if A={0,1} and N=2, then the cyclic sequence 0011 contains all
// of {00, 01, 10, 11} (wraparound is needed to construct 10). Without
// wraparound, we need to extend this to 00110.
//
// De Bruijn sequences can be constructed in many ways, but an easy one is by
// computing a Eulerian cycle over a graph that looks like this:
// https://en.wikipedia.org/wiki/De_Bruijn_sequence#Construction
//
// Solution: Hierholzer's algorithm.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

namespace {

int N, V;
vector<vector<int>> prev;

void ExtendCycle(deque<int> &cycle, int v) {
  cycle.push_front(v);
  while (!prev[v].empty()) {
    int u = prev[v].back();
    prev[v].pop_back();
    cycle.push_front(u);
    v = u;
  }
}

deque<int> FindEulerianCycle() {
  deque<int> cycle;
  int skips = 0;
  ExtendCycle(cycle, 0);
  while (skips < cycle.size()) {
    int v = cycle.front();
    cycle.pop_front();
    if (prev[v].empty()) {
      cycle.push_back(v);
      ++skips;
    } else {
      ExtendCycle(cycle, v);
      skips = 0;
    }
  }
  return cycle;
}

void Solve() {
  if (N == 1) {
    // Special case.
    cout << "01\n";
    return;
  }
  assert(N >= 2);

  V = 1 << (N - 1);
  prev = vector<vector<int>>(V);
  REP(v, V) REP(bit, 2) {
    int w = ((v << 1) | bit) & (V - 1);
    prev[w].push_back(v);
  }

  deque<int> cycle = FindEulerianCycle();
  assert(cycle.front() == 0);  // why does this happen??
  assert(cycle.size() == (1 << N) + 1);
  string bits;
  REP(i, N - 1) bits += '0';
  FOR(i, 1, cycle.size()) bits += "01"[cycle[i] & 1];
  cout << bits << '\n';
}

}  // namespace

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  cin >> N;
  Solve();
}
