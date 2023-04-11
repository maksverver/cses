#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<pair<int, int>> AB(N);
  for (auto &[a, b] : AB) cin >> a >> b;

  // Compress times into the range 0..T, with T ≤ 2N
  int T = 0;
  {
    vector<int> times;
    REP(n, N) {
      times.push_back(AB[n].first);
      times.push_back(AB[n].second);
    }
    std::sort(times.begin(), times.end());
    times.erase(std::unique(times.begin(), times.end()), times.end());
    std::map<int, int> time_index;
    T = times.size();
    REP(t, T) time_index[times[t]] = t;
    for (auto &[a, b] : AB) {
      a = time_index[a];
      b = time_index[b];
    }
  }

  // Now the actual algorithm is fairly straightforward dynamic programming.
  std::sort(AB.begin(), AB.end());
  int i = N - 1;
  vector<int> max_movies(T + 1);
  for (int t = T - 1; t >= 0; --t) {
    // We can always skip to the next time unit.
    max_movies[t] = max_movies[t + 1];

    // Consider all the movies starting at `t` (technically, we only need to
    // consider the first, which has the earliest end time, but whatever).
    while (i >= 0 && AB[i].first == t) {
      max_movies[t] = std::max(max_movies[t], max_movies[AB[i].second] + 1);
      --i;
    }
  }
  assert(i == -1);
  cout << max_movies[0] << endl;
}
