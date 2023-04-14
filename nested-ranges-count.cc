// Nested Ranges Count
// https://cses.fi/problemset/task/2168
//
// Solution:
//
// Same idea as nested-ranges-check.cc, but instead of tracking minimum/maximum
// values, we keep a set of all values, and for each range find the number of
// endpoints that are greater/smaller than the current on.

#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<class T> struct ordered_multiset :
    tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update> {};

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) {
    if (i > 0) os << ' ';
    os << v[i];
  }
  return os;
}

struct Range {
  int x, y, i;
};

// Order ranges so that the one with the lower starting point come first,
// and among ranges with the same starting point, the one with the highest
// starting point comes first. This guarantees that if range a contains b,
// a comes before b in the sorted order, even if a.first == b.first.
bool operator<(const Range &a, const Range &b) {
  return (a.x != b.x) ? a.x < b.x : a.y > b.y;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vector<Range> ranges(N);
  REP(i, N) {
    cin >> ranges[i].x >> ranges[i].y;
    ranges[i].i = i;
  }

  sort(ranges.begin(), ranges.end());

  vector<int> contained(N);
  {
    ordered_multiset<int> ys;
    for (auto [x, y, i] : ranges) {
      contained[i] += ys.size() - ys.order_of_key(y);
      ys.insert(y);
    }
  }

  std::reverse(ranges.begin(), ranges.end());

  vector<int> contains(N);
  {
    ordered_multiset<int> ys;
    for (auto [x, y, i] : ranges) {
      contains[i] += ys.order_of_key(y + 1);
      ys.insert(y);
    }
  }

  cout << contains << '\n';
  cout << contained << '\n';
}
