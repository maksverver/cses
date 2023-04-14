// Sum of Three Values
// https://cses.fi/problemset/task/1641
//
// Solution:
// We want to find three array elements (let's call the positions i, j, and k,
// and the values a, b, and c) so that a + b + c = X. We can try all pairs of
// i ≤ j, fixing a and b, and then calculcate c = X - a - b. Then we can use
// binary search to find a matching element k, for an O(N^2 log N) solution.
//
// See also: Sum of Two Values, Sum of Four Values

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  // {value, index} pairs (we need the index to print the answer)
  vector<pair<int, int>> A(N);
  REP(i, N) cin >> A[i].first, A[i].second = i + 1;

  std::sort(A.begin(), A.end());

  for (int i = 0; i < N - 2; ++i) {
    for (int j = i + 1; j < N - 1; ++j) {
      int target = X - A[i].first - A[j].first;
      if (target < A[j + 1].first) break;

      int lo = j + 1, hi = N;
      while (lo < hi) {
        int mid = lo + (hi - lo)/2;
        if (A[mid].first < target) {
          lo = mid + 1;
        } else {
          hi = mid;
        }
      }
      if (lo < N && A[lo].first == target) {
        cout << A[i].second << ' ' << A[j].second  << ' ' << A[lo].second << endl;
        return 0;
      }
    }
  }
  cout << "IMPOSSIBLE" << endl;
}
