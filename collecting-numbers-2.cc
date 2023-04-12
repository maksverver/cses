// Collecting Numbers II
// https://cses.fi/problemset/task/2217
//
// (See also collecting-numbers.cc for part 1 of this problem.)
//
// Logic:
//
// Array A contains a permutation of N integers a (1 ≤ a ≤ N). Define I[a] as
// the the 0-based index of `a` in A, so that I[A[i]] == i, with special values
// I[0] = N and I[N] = N. Define f(a) = 1 if I[a] < I[a - 1] or 0 otherwise
// (i.e., f(a) is 1 if we value `a` starts a new round). Then we can calculate
// rounds = f(1) + f(2) + .. + f(N).
//
// Given positions `i` and `j`, calculate affected elements a = A[i - 1] and
// b = B[j - 1]. It's easy to execute the swap, update A and I, and recalculate
// rounds, but doing recalculating `rounds` naively would be slow. To speed up,
// observe that the value of f(x) depends only on I[x] and I[x + 1]. When can
// therefore update `rounds` cheaply by recalculating only the affected values
// of f(x).
//
// W.l.o.g. assume a ≤ b. Then:
//
//  1. If a == b, the swap has no effect and `rounds` remains unchanged.
//
//  2. If a + 1 == b, only f(a), f(a + 1), f(b + 1) can change.
//
//  3. Otherwise, a + 1 < b, and f(a), f(a + 1), f(b), f(b + 1) can change.
//
// So we need to recalculate at most 4 terms per swap.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> A(N);
  for (int &a : A) cin >> a;

  // I[a] == index i such that A[i] == a
  vector<int> I(N + 2);
  {
    vector<pair<int, int>> ai(N);  // [{value, index}]
    REP(i, N) ai[i] = {A[i], i};
    sort(ai.begin(), ai.end());
    for (auto [a, i] : ai) I[a] = i;
  }
  I[0] = I[N + 1] = N;

  // Compute number of rounds needed to collect elements of A before swapping.
  int rounds = 0;
  REP(i, N) rounds += I[i + 1] < I[i];

  REP(m, M) {
    int i = 0, j = 0;
    cin >> i >> j;
    --i, --j;  // make indices 0-based

    if (i != j) {
      int a = A[i], b = A[j];
      // Ensure a < b. Note a != b because i != j.
      if (a > b) {
        std::swap(a, b);
        std::swap(i, j);
      }
      assert(a < b);

      // Remove obsolete terms before swapping.
      rounds -= I[a] < I[a - 1];
      rounds -= I[a + 1] < I[a];
      if (a + 1 < b) rounds -= I[b] < I[b - 1];
      rounds -= I[b + 1] < I[b];

      // Execute swap.
      A[i] = b;
      A[j] = a;
      I[a] = j;
      I[b] = i;

      // Reintroduce terms removed.
      rounds += I[a] < I[a - 1];
      rounds += I[a + 1] < I[a];
      if (a + 1 < b) rounds += I[b] < I[b - 1];
      rounds += I[b + 1] < I[b];
    }

    cout << rounds << '\n';
  }
}
