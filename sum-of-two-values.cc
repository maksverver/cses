// Sum of Two Values
// https://cses.fi/problemset/task/1640
//
// Problem:
// Given an array of integers, find a pair of distinct elements that add up to a
// given sum, and print the element indices.
//
// Solution:
// Consider a sorted array A of at least two integers, and consider the sum S of
// the first (smallest) and last (greatest) elements:
//
//  - If S = X, we have found a solution.
//  - If S > X, then the last element cannot be part of any solution, and we
//    can drop it.
//  - If S < X, then the first element cannot be part of any solution, and we
//    can drop it.
//
// So we can start by sorting the array, and pointers at the first and last
// element. At each iteration, we move either the first pointer forward or the
// second pointer backward, until we find a solution or the range is closed,
// for an O(N) solution + O(N log N) for sorting.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;

  // Pairs of {value, index} (we need the index to generate the output)
  vector<pair<int, int>> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i].first;
    A[i].second = i + 1;
  }

  std::sort(A.begin(), A.end());

  int i = 0, j = N - 1;
  while (i < j) {
    int S = A[i].first + A[j].first;
    if (S > X) --j; else if (S < X) ++i; else break;
  }

  if (i < j) {
    cout << A[i].second << ' ' << A[j].second << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}
