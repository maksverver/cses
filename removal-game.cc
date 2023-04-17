// Removal Game
// https://cses.fi/problemset/task/1097
//
// Fun problem!
//
// We can calculate the maximum score difference between the next and
// previous player using dynamic programming.
//
// f(i, j) is the maximum score difference on A[i:j] for the next player
//
// f(i, i) = A[i]
// f(i, j) = max(A[i] - f(i + 1, j), A[j] - f(i, j + 1))   (i < j)
//
// Since the sum of scores of both players is always equal to the sum of the
// values in the array we can reconstruct individual player scores from the
// difference:
//
//   a + b = total
//   a - b = diff
//   b = diff + a
//   2a + diff = total
//   a = (diff + total)/2
//
// (It's easy to see that diff and total have the same parity, so their sum
// will be divisible by 2.)
//
// Alternatively, we could alternate between maximizing/minimizing, since we
// know which player moves next from the parity of (j - i), but I like my
// solution better :-) It's like the difference between minimax and negamax.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  assert(N > 0);  // otherwise the score is always 0
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  // m[i][j] == score difference for the next player on A[i..j] (inclusive)
  vector<vector<int64_t>> m(N, vector<int64_t>(N));
  for (int j = 0; j < N; ++j) {
    m[j][j] = A[j];
    for (int i = j - 1; i >= 0; --i) {
      m[i][j] = max(A[i] - m[i + 1][j], A[j] - m[i][j - 1]);
    }
  }

  int64_t max_diff = m[0][N - 1];
  int64_t total = accumulate(A.begin(), A.end(), int64_t{0});
  int64_t max_score = (max_diff + total)/2;
  cout << max_score << '\n';
}
