// Tasks and Deadlines
// https://cses.fi/problemset/task/1630
//
// Solution: it's optimal to process tasks in order of duration.
// Proof: so trivial that I leave it as an exercise to the reader :-)

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<pair<int, int>> A(N);
  for (auto &[a, d] : A) cin >> a >> d;
  std::sort(A.begin(), A.end());

  int64_t t = 0, answer = 0;
  for (auto [a, d] : A) {
    t += a;
    answer += d - t;
  }
  cout << answer << '\n';
}
