// Maximum Subarray Sum
// https://cses.fi/problemset/task/1643
//
// Given an array of integers, find the maximum subarray sum.
//
// Solution:
// Let's call P[i] = A[1] + A[2] + ... + A[i - 1] (i.e. the sum of prefix of
// length i). Then the sum of a subarray A[i..j] = P[j] - P[i - 1]. It's easy
// to go through the array from left to right and keep track of the current
// prefix sum (P[j]) then to maximize the sum P[j] - P[i - 1] we should use the
// the minimum value of P[i - 1] (1 ≤ i ≤ j): it's easy to track this minimum
// too.
//
// This leads to an O(N) time O(1) space algorithm.
//
// Note: slightly tricky is that we are required to give the sum of a nonempty
// substring, so we cannot use 0 as the default answer, since if all elements
// of A are negative, A will be negative too!
//
// See also maximum-subarray-sum-3.cc for slightly simpler implementation, or
// maximum-subarray-sum-2-too-complicated.cc for one that's unnecessarily
// complex.
//
// See also maximum-subarray-sum-II.cc for a variation of this problem.

#include <algorithm>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  int64_t answer = numeric_limits<int64_t>::min();
  int64_t prefix_sum = 0, min_prefix_sum = 0;
  while (N-- > 0) {
    int x = 0;
    cin >> x;
    prefix_sum += x;
    answer = std::max(answer, prefix_sum - min_prefix_sum);
    min_prefix_sum = std::min(min_prefix_sum, prefix_sum);
  }
  cout << answer << endl;
}
