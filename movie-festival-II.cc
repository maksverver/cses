// Movie Festival II
// https://cses.fi/problemset/task/1632
//
// Similar to movie-festival.cc: we sort movies by end-time, then consider them
// in order, and if someone can attend the movie, they should.
//
// The only tricky part is that if multiple people can attend the movie, we
// should the person who is free the latest, so that people who are free earlier
// can still attend movies that end later but start earlier.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, K = 0;
  cin >> N >> K;
  vector<pair<int, int>> BA(N);
  for (auto &[b, a] : BA) cin >> a >> b;

  // Sort by end times (ascending)
  std::sort(BA.begin(), BA.end());

  // Track time at which each person is available agian.
  std::multiset<int> ends;
  REP(_, K) ends.insert(0);

  int answer = 0;
  for (auto [b, a] : BA) {
    // Select person who is available at or before time `a`.
    auto it = ends.upper_bound(a);
    if (it == ends.begin()) continue;
    --it;
    assert(*it <= a);
    ends.erase(it);
    ends.insert(b);
    ++answer;
  }
  cout << answer << '\n';
}
