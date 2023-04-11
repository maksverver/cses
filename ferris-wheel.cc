// Ferris Wheel
// https://cses.fi/problemset/task/1090
//
// Solution: greedy algorithm.
//
// Sort the people by their weight. If we can put the heaviest and lightest
// person together, we do so. Otherwise, put the heaviest person by themselves.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> P(N);
  for (int &p : P) cin >> p;

  std::sort(P.begin(), P.end());

  int answer = 0;
  int i = 0, j = N - 1;
  while (i < j) {
    if (P[i] + P[j] <= X) ++i;
    --j;
    ++answer;
  }
  if (i == j) ++answer;

  cout << answer << '\n';
}
