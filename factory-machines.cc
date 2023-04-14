// Factory Machines
// https://cses.fi/problemset/task/1620
//
// Solution: for a given time, we can calculate easily how many products will
// be made, and this number increases with time, so we can binary search for the
// minimum time.
//
// We need to be careful to avoid integer overflow!

#include <bits/stdc++.h>
#include <limits>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  int64_t T = 0;
  cin >> N >> T;
  vector<int64_t> A(N);
  for (int64_t &a : A) cin >> a;

  // Returns how many products are made in `time` units of time.
  auto calc = [&](int64_t time) {
    int64_t made = 0;
    for (int64_t a : A) made += time/a;
    return made;
  };

  int64_t lo = 0, hi = 1;
  while (calc(hi) < T) {
    hi *= 2;
  }
  while (lo < hi) {
    int64_t mid = lo + (hi - lo)/2;
    if (calc(mid) < T) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  cout << lo << '\n';
}
