// Stick Lengths
// https://cses.fi/problemset/task/1074
//
// Solution:
// The optimal length is the median element.
//
// Rationale: let's say we pick some target L and calculate the total cost.
//
// Let's say there are A sticks which are strictly shorter than L, and B
// sticks that have length greater than or equal to L. Then if A > B, it
// is beneficial to decrease L by 1, which decreases the cost by A - B.
//
// This means we should keep decreasing L until the number of sticks less than
// L is not greater than the number of sticks with length equal to or greater
// than L. And symmetrically, the same thing in the other direction.
//
// That means the only positions where we shouldn't move L are at the median
// value (if we have an odd number of sticks) or between the two middle values
// (if we have an even number of sticks).

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

  int L = A[A.size()/2];
  int64_t answer = 0;
  for (int l : A) answer += abs(l - L);

  cout << answer << endl;
}
