// Sum of Four Values
// https://cses.fi/problemset/task/1642
//
// Fun! See also: Sum of Two Values, Sum of Three Values
//
// Solution:
//
// Since N ≤ 1000, it is feasible to precompute the sums of all pairs of
// elements. Then we can iterate over the sums S and check if there is a way
// to create sum X - S. The tricky part is that we must construct the sum using
// four *distinct* elements (by position, not necessarily by value).
//
// We could store a full list of pairs for each sum, but comparing these list
// might be too slow (e.g. for "1 1 1 1 1 1 1 1 10" there are lots of ways to
// make 11, but we cannot make sum 22 without reusing the final 10 element).
//
// Instead, we will only store two pairs: (i1, j1) where j1 is minimal, and
// another pair (i2, j2) where i2 is maximal. The rationale is that if there
// is a solution, there must be a solution with indices i1 < j1 < i2 < j2,
// and in that case S = A[i1] + A[j1] and X - S = A[i2] + A[j2].
//
// The solution runs in O(N^2) time when using std::unordered_map<>, or in
// O(N^2 log N) when using std::map<>.

#include <bits/stdc++.h>

using namespace std;

struct State {
  int i1 = 0, j1 = 0;
  int i2 = 0, j2 = 0;

  void add(int i, int j) {
    assert(i >= 0 && j >= 1 && i < j);
    if (j1 == 0 || j < j1) i1 = i, j1 = j;
    if (j2 == 0 || i > i2) i2 = i, j2 = j;
  }
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int64_t> A(N);
  for (int64_t &a : A) cin >> a;

  unordered_map<int64_t, State> states_by_sum;

  for (int i = 0; i < N - 1; ++i) {
    for (int j = i + 1; j < N; ++j) {
      states_by_sum[A[i] + A[j]].add(i, j);
    }
  }

  for (const auto &[sum1, state1] : states_by_sum) {
    auto it = states_by_sum.find(X - sum1);
    if (it != states_by_sum.end()) {
      const auto &[sum2, state2] = *it;
      if (state1.j1 < state2.i2) {
        cout << state1.i1 + 1 << ' ' << state1.j1 + 1 << ' '
          << state2.i2 + 1 << ' ' << state2.j2 + 1 << endl;
        return 0;
      }
    }
  }

  cout << "IMPOSSIBLE" << endl;
}
