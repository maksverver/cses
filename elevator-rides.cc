// Elevator Rides
// https://cses.fi/problemset/task/1653
//
// Bin packing. Given an array A of size N, partition it into a minimal number
// of subsets, such that the sum of each subset is less than or equal to X.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

constexpr unsigned Bit(int i) { return 1u << i; }

int Solve(int N, int X, const vector<int> &A) {
  vector<int> min_trips(1 << N, N);
  vector<int> last_weight(1 << N, X);
  min_trips[0] = 0;
  last_weight[0] = X;
  REP(m, Bit(N)) REP(i, N) if (m & Bit(i)) {
    int new_min_trips = min_trips[m - Bit(i)];
    int new_last_weight = last_weight[m - Bit(i)] + A[i];
    if (new_last_weight > X) {
      new_min_trips++;
      new_last_weight = A[i];
    }
    if (std::tie(new_min_trips, new_last_weight) < std::tie(min_trips[m], last_weight[m])) {
      min_trips[m] = new_min_trips;
      last_weight[m] = new_last_weight;
    }
  }
  return min_trips.back();
}

int main() {
  int N = 0, X = 0;
  cin >> N >> X;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  cout << Solve(N, X, A) << endl;
}
