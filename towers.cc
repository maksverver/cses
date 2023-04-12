// Towers
// https://cses.fi/problemset/task/1073
//
// Solution:
// For each new cube, we greedily place it on top of the tower with the
// smallest size that is still greater than the current cube.
//
// Practically, we can do this by keeping a vector T of tower sizes. For each
// cube size `x`, we can use a binary search to find the position where to
// place the next cube, or if there is none, append it at the end.
//
// This guarantees the vector will always remain in nondescending order, because
// we only append a value `x` if all preceding values are less than or equal
// to `x`, and when we replace an index `i` by `x` instead, that means that
// either T[i] is the last element, or T[i + 1] >= x.
//
// The solution runs in O(N log N) time and O(N) space.
//
// Proof that the greedy solution works:
//
// Let's pretend that instead of creating new towers, we just start with `N`
// towers that all have a bottom cube of size infinity, and we minimize the
// number of towers with more than 1 cube on top. This the same problem, but
// now we can assume we always place the cube on some valid tower.
//
// A sorted list of towers with sizes A is strictly better than B if
// A[i] >= B[i] for all i, since any placements of cubes on B also works for A.
// We we have a cube of size x, and a least index `i` such that x < A[i],
// then any choice of j > i would either be just as good (when A[i] = A[j]), or
// worse (when A[i] < A[j]), because the resulting sequences differ only in
// positions `i` and `j`, and the sorted sequences contain {x, A[j]} vs
// {x, A[i]}, so since A[j] >= A[i], the former is strictly better.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  // For each tower, the size of the cube on top. These towers will always
  // appear in increasing order.
  vector<int> towers;

  int N = 0;
  cin >> N;
  while (N--) {
    int x = 0;
    cin >> x;

    // Binary search for first position
    auto it = std::upper_bound(towers.begin(), towers.end(), x);
    if (it != towers.end()) {
      *it = x;
    } else {
      towers.push_back(x);
    }
  }

  cout << towers.size() << endl;
}
