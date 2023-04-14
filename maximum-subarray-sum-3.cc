// Maximum Subarray Sum
// https://cses.fi/problemset/task/1643
//
// Given an array of integers, find the maximum subarray sum.
//
// We go through the array from left to right, keeping track of the best sum
// ending at the last position. At every position, we can choose to either
// extend the previous sum, or start a new one. Starting a new one is better if
// the previous sum was negative.


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
