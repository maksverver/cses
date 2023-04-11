// Apple Division
// https://cses.fi/problemset/task/1623

// Approach: brute force. Since N ≤ 20 we can enumerate all possible divisions.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  int N = 0;
  cin >> N;
  assert(N > 0);
  vector<int> P(N);
  for (int &p : P) cin >> p;

  auto calc = [&](unsigned mask) {
    // This operation runs in O(N) time. We could precompute the sum per mask in
    // O(2^N) time and O(2^N) memory, which would reduce total the runtime
    // complexity from O(N × 2^N) to O(N), but I don't think it's worth it.
    int64_t a = 0, b = 0;
    REP(i, N) ((mask & (1 << i)) ? a : b) += P[i];
    return abs(a - b);
  };

  // Note that we only iterate over half the masks because the problem is symmetric:
  // diff(x) == diff(~x).
  int64_t answer = calc(0);
  for (unsigned mask = 1; mask != 1u << (N - 1); ++mask) {
    answer = std::min(answer, calc(mask));
  }
  cout << answer << endl;
}
