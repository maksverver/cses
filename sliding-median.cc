// Sliding Median
// https://cses.fi/problemset/task/1076

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

  // The set of the latest K pairs {A[i], i} (index included to make elements distinct)
  set<pair<int, int>> values;
  REP(i, K) values.insert({A[i], i});

  // it always points to the median element in `values`
  auto it = values.begin();
  const int median_index = (K - 1) / 2;
  REP(i, median_index) ++it;

  cout << it->first;
  FOR(i, K, N) {
    pair<int, int> old_pair = {A[i - K], i - K};
    pair<int, int> new_pair = {A[i], i};
    values.insert(new_pair);
    if (new_pair < *it) --it;
    if (old_pair == *it) {
      it = values.erase(values.find(old_pair));
    } else {
      values.erase(old_pair);
      if (old_pair < *it) ++it;
    }
    cout << ' ' << it->first;
  }
  cout << endl;
}

