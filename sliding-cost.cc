// Sliding Cost
// https://cses.fi/problemset/task/1077
//
// Similar to Sliding Median: it is optimal to make all elements equal to the
// median. So we track the median, as in sliding-median.cc, and do a little
// extra bookkeeping to track the total cost.

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

  int64_t cost = 0;
  REP(i, K) cost += abs(A[i] - it->first);

  cout << cost;
  FOR(i, K, N) {
    // This is the same as in sliding-median.cc: remove/insert old/new elements
    // while making sure `it` keeps pointing to `median_index`.
    int old_median = it->first;
    pair<int, int> old_pair = {A[i - K], i - K};
    pair<int, int> new_pair = {A[i], i};
    cost -= abs(A[i - K] - old_median);
    cost += abs(A[i] - old_median);
    values.insert(new_pair);
    if (new_pair < *it) --it;
    if (old_pair == *it) {
      it = values.erase(values.find(old_pair));
    } else {
      values.erase(old_pair);
      if (old_pair < *it) ++it;
    }

    // This part is slightly tricky. If the median increased, that means the cost
    // was reduced for the median element and all to the right, while it
    // increased for those the left. Symmetrically, if the median decreased, the
    // cost reduced for the median element and all to the left, and increased
    // for those on the right. If K is odd, then the difference between the two
    // sides is always 1, but if K is even, then the difference is 0 or 2
    // depending.
    //
    // For example: if we go from 2 3 8 (median = 3, cost = 1 + 0 + 5 = 6) to
    // 3 8 9 (cost = 0 + 5 + 6 = 11), then we adjust the median from 3 to 8, we
    // get cost = 5 + 0 + 1 = 6, i.e., one term increased by 5 and two terms
    // decreased by 5, for a net reduction of 5.
    //
    // If we have an even number of elements, say 1 2 3 4, then moving the median
    // from 3 to 2 means cost goes from 2 + 1 + 0 + 1 = 4 to 1 + 0 + 1 + 2 = 4,
    // which is no net change because we increased 2 terms and decreased 2
    // terms, but from 1 to 2 would go from 0 + 1 + 2 + 3 = 6 to
    // 1 + 0 + 1 + 2 = 4, a reduction of 2 not 1, because we increased 1 term
    // and decreased 3.
    int new_median = it->first;
    if (old_median < new_median) {
      cost -= (new_median - old_median) * (2 - K % 2);
    } else if (old_median > new_median) {
      cost -= (old_median - new_median) * (K % 2);
    }
    cout << ' ' << cost;
  }
  cout << endl;
}

