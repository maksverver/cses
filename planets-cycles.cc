// Planets Cycles
// https://cses.fi/problemset/task/1751
//
// Fun problem!
//
// Problem:
//
// For a graph where each vertex has exactly 1 outgoing edge, compute for
// each vertex the number of distinct vertices reachable.
//
// Solution:
//
// We can identify the vertices that do not lie on a cycle by searching for
// a vertex v with indegree 0, then remove the edge (v, next[v]), and so on.
// If we added vertices with indegree 0 to a vector (`stack`) in the order
// we find them, then if there is a path from stack[i] to stack[j], i < j.
//
// Now, all the vertices that remain that haven't been added to `stack` yet
// must be part of a cycle (there may be multiple cycles, since the graph is
// not guaranteed to be connected). We can simply identify each cycle separately
// and calculate the answer for the vertices on the cycle as the length of the
// cycle.
//
// Now we can go back to the vertices on the stack, removing them in reverse
// order. Since each vertex was added to the stack before its successor, we
// know the successor's answer is already computed when we reach its
// predecessor.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) {
    if (i > 0) os << ' ';
    os << v[i];
  }
  return os;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vector<int> next(N);
  for (int &x : next) cin >> x, --x;

  vector<int> indegree(N);
  REP(i, N) ++indegree[next[i]];

  vector<char> seen(N, false);

  vector<int> stack;
  REP(i, N) if (!seen[i]) {
    for (int v = i; indegree[v] == 0; v = next[v]) {
      seen[v] = true;
      stack.push_back(v);
      --indegree[next[v]];
    }
  }

  vector<int> answers(N, -1);
  vector<int> cycle;  // declared outside the loop so I can reuse the memory
  REP(i, N) if (!seen[i]) {
    // Identify a new cycle starting at `i`
    int v = i;
    cycle.clear();
    do {
      seen[v] = true;
      cycle.push_back(v);
      v = next[v];
    } while (v != i);

    // Calculate answer for vertices lying on this cycle.
    for (int v : cycle) answers[v] = cycle.size();
  }

  // Calculate answer for vertices not lying on a cycle.
  while (!stack.empty()) {
    int v = stack.back();
    stack.pop_back();
    answers[v] = answers[next[v]] + 1;
  }

  cout << answers << endl;
}
