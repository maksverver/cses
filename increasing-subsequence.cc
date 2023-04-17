// Increasing Subsequence
// https://cses.fi/problemset/task/1145
//
// Classic longest-increasing-subsequence problem.
//
// Rationale: we go through the input one by one, and for each increasing
// subsequence of length L, we keep the minimum-possible last number.
//
// Example (the contents of each column correspond with `last` in main()):
//
//   input:  7 3 5 3 6 2 9 8
//
//   len=1:  7 3 3 3 3 2 2 2
//   len=2:      5 5 5 5 5 5
//   len=3:          6 6 6 6
//   len=4:              9 8
//
// The elements of `last` are themselves in strictly increasing order because
// if last[l] = x (l > 1), then there is a subsequence of length l - 1 that
// ends with a value < x, so last[l - 1] must be < x, or it's not the
// minimum-possible last digit.
//
// For an input number x, let `i` be the minimum index such that x ≤ last[i]
// (or length of `last` if there is none). Then `i-1` is the length of the
// longest sequence we can extend, and we can set last[i] = x (creating a
// new entry if index `i` did not yet exist).
//
// Note that overwriting last[i] will never increase an existing value, because
// last[i] ≥ x by definition. Similarly, all values last[j] < x for all j < i,
// so there is no need to consider sequences shorter than `i` that end with x.
//
// Because values of `last` are sorted, we can use binary search to find `i`
// efficiently.
//
// If we needed to extract the elements of the LIS (in addition to its size),
// we should also store the previous element index, but that's not needed for
// this problem.
//
// The solution runs in O(N log N) time and O(N) space.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> last;  // last[i] == last number in the LIS of length (i + 1)
  while (N-- > 0) {
    int x = 0;
    cin >> x;
    auto it = std::lower_bound(last.begin(), last.end(), x);
    if (it == last.end()) {
      last.push_back(x);
    } else {
      *it = x;
    }
  }
  cout << last.size() << '\n';
}
