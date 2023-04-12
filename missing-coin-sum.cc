// Missing Coin Sum
// https://cses.fi/problemset/task/2183
//
// (Fun problem! Much easier than it first seems.)
//
// Problem:
//
// Given a bag (multiset) of coins of positive values, calculate the smallest
// positive number that is not the sum of a subset of coins.
//
// Solution:
//
// Sort the coins. We can calculate a running prefix S[i] of the first `i` coins
// and stop when we the next coin C[i] > S[i] + 1. Then our answer is S[i] + 1.
//
// Proof:
//
// One way to calculate the possible subset sums is to define:
//
//  SS[0] = {0}
//  SS[i] = {s + C[i], where s in SS[i - 1]}
//
// For this algorithm, the order in which we process the coins doesn't matter,
// but the sets may grow very large.
//
// If we sort the coins first, then we can observe that if SS[i] is missing a
// value X < C[i], then all SS[j] with j > i will also miss value X, because we
// cannot construct it by adding a coin with value greater than X. We want to
// find the lowest value of X.
//
// That means we only need to consider sets SS[i] such that SS[i] contains all
// values between 0 and C[i] - 1 (inclusive). In fact, we can prove a stronger
// statement: if SS[i] contains 0 through C[i] - 1, then SS[i] = {0..S[i]}.
//
// Proof by induction:
//
// Base case: it's trivially true that SS[0] = {0} = {0..S[0]}
//
// If SS[i - 1] = {0..S[i - 1]} and S[i - 1] < C[i] - 1, we cannot construct
// C[i] - 1, so the precondition doesn't hold for SS[i] or any later set.
// Otherwise, we can construct SS[i] = {0..S[i - 1] + C[i]} = {0..S[i]}.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (int &i : A) cin >> i;

  std::sort(A.begin(), A.end());

  int64_t max_possible = 0;
  for (int a : A) {
    if (max_possible < a - 1) break;
    max_possible += a;
  }

  cout << max_possible + 1 << endl;
}
