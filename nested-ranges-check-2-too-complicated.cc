// Nested Ranges Check
// https://cses.fi/problemset/task/2168
//
// Solution:
// If we sort the ranges by the start point (ascending) and end point
// (descending), then we know a range `a` can contain a range `b` only if it
// occurs before it in the sorted list.
//
// We can go through the ranges in order, keeping track of the endpoints of the
// preceding ranges in a sorted set. The current range is contained by some
// range if the highest endpoint in the set is greater than or equal to the
// current range's endpoint.
//
// We can use the same logic to mark ranges that contain another range, but we
// need to be careful to avoid doing duplicate work, so the solution remains
// O(N log N) overall.
//
// NOTE: this is really too complicated! See nested-ranges-check.cc for a much
// nicer implementation.

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

  vector<int> contains(N);
  vector<int> contained(N);

  set<int> ends;

  // Separate set of endspoints associated with range index, so that we can mark
  // the ranges that contain something. We will remove elements once we mark
  // each range as contained, to avoid duplicate work.
  set<pair<int, int>> uncontained_ends;

  for (auto [x, y, i] : ranges) {

    // Remove all ranges that end before x
    {
      auto it = ends.begin();
      while (it != ends.end() && *it < x) ++it;
      ends.erase(ends.begin(), it);
    }
    // Same thing, but for uncontained_ends
    {
      auto it = uncontained_ends.begin();
      while (it != uncontained_ends.end() && it->first < x) ++it;
      uncontained_ends.erase(uncontained_ends.begin(), it);
    }

    // Check if range i is contained by some other range.
    {
      auto it = ends.end();
      if (it != ends.begin() && *--it >= y) {
        contained[i] = true;
      }
    }

    // Mark all possible ranges that contain range i
    {
      // The code would be less ugly using rbegin()/rend() but unfortunately
      // C++ doesn't support deleting using a reverse-iterator.
      auto it = uncontained_ends.end();
      auto delete_begin = it;
      while (it != uncontained_ends.begin() && (--it)->first >= y) {
        contains[it->second] = true;
        delete_begin = it;
      }
      // Remove elements to prevent markign a range more than once.
      uncontained_ends.erase(delete_begin, uncontained_ends.end());
    }

    // Insert range
    ends.insert(y);
    uncontained_ends.insert({y, i});
  }

  cout << contains << '\n';
  cout << contained << '\n';
}
