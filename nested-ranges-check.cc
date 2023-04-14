// Nested Ranges Check
// https://cses.fi/problemset/task/2168
//
// Solution:
// If we sort the ranges by the start point (ascending) and end point
// (descending), then we know a range `a` can contain a range `b` only if it
// occurs before it in the sorted list.
//
// We can go through the ranges in order, keeping track of the maximum endpoint
// of an earlier range; if that maximum is greater than the current range's
// endpoint, the current range is contained by some earlier range.
//
// Similarly, we can go through the ranges in reverse order, keeping track of
// the minimum endpoint of a later range; if that minimum is less than the
// current range's endpoint, the current range contains some later range.
//
// See also nested-ranges-count.cc for a more general version of this problem,
// and nested-ranges-check-2-too-complicated.cc for an alternate implementation
// using sets.

#include <bits/stdc++.h>

using namespace std;

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
  int max_y = -1;
  for (auto [x, y, i] : ranges) {
    contained[i] = y <= max_y;
    max_y = std::max(max_y, y);
  }

  std::reverse(ranges.begin(), ranges.end());

  vector<int> contains(N);
  int min_y = numeric_limits<int>::max();
  for (auto [x, y, i] : ranges) {
    contains[i] = y >= min_y;
    min_y = std::min(min_y, y);
  }

  cout << contains << '\n';
  cout << contained << '\n';
}
