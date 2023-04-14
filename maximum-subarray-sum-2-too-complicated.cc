// Maximum Subarray Sum
// https://cses.fi/problemset/task/1643
//
// Given an array of integers, find the maximum substring sum.
//
// Solution:
// Precalculate C[j] = sum of A[i..j). Then the sum of a substring A[i..j) can
// be calculated as C[j] - C[i]. This means for a fixed `i`, we want to use the
// value of j where C[j] is maximum. We only need to loop over possible `i`s
// from high to low, and we can track the maximum C[j] for j >= i as we go,
// and keep the maximum of the calculated differences.
//
// Note: slightly tricky is that we are required to give the sum of a nonempty
// substring, so we cannot use 0 as the default answer, since if all elements
// of A are negative, A will be negative too!
//
// See also maximum-subarray-sum-II.c

#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (int &i : A) cin >> i;

  // C[i] = sum of A[0..i)
  vector<int64_t> C(N + 1);
  REP(i, N) C[i + 1] = C[i] + A[i];

  int64_t answer = A[N - 1];
  int64_t max_c = C[N];
  for (int i = N - 1; i >= 0; --i) {
    answer = std::max(answer, max_c - C[i]);
    max_c = std::max(max_c, C[i]);
  }
  cout << answer << endl;
}
