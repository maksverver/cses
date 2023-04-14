// Subarray Sums I
// https://cses.fi/problemset/task/1660
//
// See also subarray-sums-II.cc
//
// Solution: two pointer technique (similar to Sum of Two Values, actually!)

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  int count = 0;
  for (int i = 0, j = 0, sum = 0; i < N; ++i) {
    while (j < N && sum < X) sum += A[j++];
    if (sum == X) ++count;
    sum -= A[i];
  }
  cout << count << endl;
}
