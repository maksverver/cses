// Rectangle Cutting
// https://cses.fi/problemset/task/1744
//
// Note that we need to cut the rectangle into squares, not necessarily unit
// squares! For each rectangle A x B we can try the possible (A - 1) horizontal
// and (B - 1) vertical cuts.
//
// Due to rotational symmetry, we only actually need to try ceil(A/2) +
// ceil(B/2) cuts. That means the total number of iterations in the loop is
// something like A × B × A / 4 + A × B × B / 4; when A and B are bounded by N
// this is N^3 / 4 which for N=500 is only about 31.5 million.
//
// We could optimize this further by only calculating entries where A < B but
// it makes the logic more complicated and would only decrease runtime by a
// factor 2, so it's probably not worth it.

#include <bits/stdc++.h>

using namespace std;

int main() {
  int A = 0, B = 0;
  cin >> A >> B;
  vector<vector<int>> m(A + 1, vector<int>(B + 1));
  for (int i = 1; i <= A; ++i) m[i][1] = i - 1;
  for (int j = 1; j <= B; ++j) m[1][j] = j - 1;
  for (int i = 2; i <= A; ++i) {
    for (int j = 2; j <= B; ++j) {
      if (i == j) {
        m[i][j] = 0;
      } else {
        m[i][j] = numeric_limits<int>::max();
        for (int k = 1; k <= i - k; ++k) m[i][j] = min(m[i][j], 1 + m[k][j] + m[i - k][j]);
        for (int k = 1; k <= j - k; ++k) m[i][j] = min(m[i][j], 1 + m[i][k] + m[i][j - k]);
      }
    }
  }
  cout << m[A][B] << '\n';
}
