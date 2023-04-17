// Projects
// https://cses.fi/problemset/task/1140
//
// Solution:
//
// If we sort the vector of projects P by start date, we can calculate the
// maximum reward for each suffix of P. For each project, we either skip the
// current project, or we take it (taking its reward) and the move on to the
// first project that starts after the current project's finish date. We can
// find the earliest later project with binary search, for an
// O(N log N) solution.
//
// f(i) is the max reward of P[i..N)
//
//   f(N) = 0
//   f(i) = max(f(i + 1), f(j) + reward[i] where j is the least j such that start[j] > finish[i])

#include <bits/stdc++.h>

using namespace std;

struct Project {
  int start, finish, reward;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<Project> P(N);
  for (auto &[start, finish, reward] : P) cin >> start >> finish >> reward;

  std::sort(P.begin(), P.end(),
      [](const Project &a, const Project &b) { return a.start < b.start; });

  std::vector<int64_t> max_reward(N + 1);
  for (int i = N - 1; i >= 0; --i) {
    int j = std::lower_bound(P.begin(), P.end(), P[i].finish,
        [](const Project &p, int t) { return p.start <= t; }) - P.begin();
    max_reward[i] = std::max(max_reward[i + 1], max_reward[j] + P[i].reward);
  }
  cout << max_reward[0] << '\n';
}
