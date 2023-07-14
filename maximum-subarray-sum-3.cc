// Maximum Subarray Sum
// https://cses.fi/problemset/task/1643
//
// Given an array of integers, find the maximum subarray sum.
//
// We go through the array from left to right, keeping track of the best sum
// ending at the last position. At every position, we can choose to either
// extend the previous sum, or start a new one. Starting a new one is better if
// the previous sum was negative.
//
// This is effectively the same as maximum-subarray-sum-1.cc. Consider the
// algorithm there:
//
//   for each x:
//     prefix_sum += x
//     answer = max(answer, prefix_sum - min_prefix_sum)
//     min_prefix_sum = min(min_prefix_sum, prefix_sum)
//
// But since min_prefix_sum can only decrease, we might as well subtract it from
// prefix_sum every time and set it to zero (this means `current_sum` now always
// contains the value of `prefix_sum - min_prefix_sum` above).
//
//   for each x:
//     current_sum += x
//     answer = max(answer, current_sum - min_prefix_sum)
//     min_prefix_sum = min(min_prefix_sum, current_sum)
//     current_sum -= min_prefix_sum
//     min_prefix_sum = 0
//
// But now min_prefix_sum is always 0 before the loop, so we can remove it:
//
//   for each x:
//     current_sum += x
//     answer = max(answer, current_sum)
//     if sum < 0:
//       current_sum = 0
//
// Which is basically the logic we have here.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  int64_t answer = numeric_limits<int64_t>::min();
  int64_t current_sum = 0;
  while (N-- > 0) {
    int x = 0;
    cin >> x;
    if (current_sum < 0) current_sum = 0;
    current_sum += x;
    answer = std::max(answer, current_sum);
  }
  cout << answer << endl;
}
