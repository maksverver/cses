// Array Division
// https://cses.fi/problemset/task/1085
//
// Binary search for the maximum sum.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, K = 0;
  cin >> N >> K;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  auto test = [&](int64_t max_sum) {
    int i = 0, parts = 0;
    while (i < N && parts < K) {
      ++parts;
      int64_t sum = 0;
      while (i < N && sum + A[i] <= max_sum) sum += A[i++];
    }
    return i == N;
  };

  int64_t lo = 0;
  int64_t hi = accumulate(A.begin(), A.end(), int64_t{0});
  while (lo < hi) {
    int64_t mid = lo + (hi - lo)/2;
    if (test(mid)) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  cout << lo << endl;
}
