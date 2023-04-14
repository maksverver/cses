// Subarray Sums II
// https://cses.fi/problemset/task/1661
//
// (Note the problem statement isn't clear whether empty subarrays count as
// having sum 0 or not. I chose to exclude them.)
//
// Solution:
//
// Define P[i] = A[0] + A[1] + .. + A[i - 1] (i.e. the prefix sum of length i).
// Then the subarray sum A[i..j] = P[j + 1] - P[i]. We can run through the array
// from left to right and keep track of the current prefix sum, `sum`. Then we
// only need to count the number of earlier prefixes with sum `sum - X`; this
// we can do with a std::map<>.
//
// Note: std::multiset<> is not a good idea here, because std::multiset::count()
// takes O(N) time!
//
// See also subarray-sums-I.cc

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  // sum_count[x] is the number of prefixes that sum to x
  map<int64_t, int> sum_count;

  int64_t sum = 0, answer = 0;
  for (int i = 0; i < N; ++i) {
    ++sum_count[sum];
    sum += A[i];
    answer += sum_count[sum - X];
  }
  cout << answer << endl;
}
