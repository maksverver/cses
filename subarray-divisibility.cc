// Subarray Divisibility
// https://cses.fi/problemset/task/1662
//
// This is the same as subarray-sums-II.cc except we search for sums modulo N?

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  // sum_count[x] is the number of prefixes that sum to x (mod N)
  vector<int> sum_count(N);

  int64_t sum = 0, answer = 0;
  for (int i = 0; i < N; ++i) {
    ++sum_count[sum];
    sum = ((sum + A[i]) % N + N) % N;
    answer += sum_count[sum];
  }
  cout << answer << endl;
}
