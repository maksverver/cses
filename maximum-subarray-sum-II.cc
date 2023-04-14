// Maximum Subarray Sum II
// https://cses.fi/problemset/task/1644
//
// See also maximum-subarray-sum.cc
//
// Solution: sliding window algorithm.
//
// Let C[i] be the prefix sum of length `i`. We want to maximize the subarray
// sum A[i:j) = C[j] - C[i], such that j - B ≤ i ≤ j - A. We can keep the valid
// values of C[i] in a multiset, add C[j - A] before looking up the minimum,
// and remove C[j - B] afterwards.
//
// The trickiest part is avoid off-by-1 errors!
//
// Alternative: use something like a segment tree to look up maximums over
// arbitrary ranges.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, A = 0, B = 0;
  cin >> N >> A >> B;
  vector<int> X(N);
  for (int &x : X) cin >> x;

  vector<int64_t> C(N + 1);
  REP(i, N) C[i + 1] = C[i] + X[i];

  multiset<int64_t> in_range;
  int64_t answer = numeric_limits<int64_t>::min();
  FOR(i, A, N + 1) {
    in_range.insert(C[i - A]);
    answer = std::max(answer, C[i] - *in_range.begin());
    if (i >= B) in_range.erase(in_range.find(C[i - B]));
  }
  cout << answer << endl;
}
