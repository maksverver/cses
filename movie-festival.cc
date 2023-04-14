// Movie Festival
// https://cses.fi/problemset/task/1629
//
// See also movie-festival-II.cc

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<pair<int, int>> BA(N);
  for (auto &[b, a] : BA) cin >> a >> b;

  // Sort by end times (ascending)
  std::sort(BA.begin(), BA.end());

  // Greedily pick each movie that ends soonest.
  int time = 0, count = 0;
  for (auto [b, a] : BA) {
    if (a >= time) {
      time = b;
      ++count;
    }
  }
  cout << count << endl;
}
