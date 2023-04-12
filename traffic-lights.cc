// Traffic lights
// https://cses.fi/problemset/task/1163
//
// Solution:
// We start with a single segment [0, X], and for each incoming point, we split
// an existing segment. For example, after the first point we will have two
// segments, [0, p] and [p, X].
//
// To make it efficiently, we can use std::set<>, which is an ordered container.
// If we create two sets, one with <start, length> pairs, and a second with
// <length, start> pairs, then we can use the first set to find the segment
// to split, and the second set to find the longest length of a segment.
//
// (Alternatively, the sets could store <start, end> and <length, end> pairs
// respectively, or some variation.)

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int X = 0, N = 0;
  cin >> X >> N;

  set<pair<int, int>> segments_by_start;   // set of {start, length} pairs
  set<pair<int, int>> segments_by_length;  // set of {length, start} pairs

  segments_by_start.insert({0, X});
  segments_by_length.insert({X, 0});

  REP(n, N) {
    int p = 0;
    cin >> p;

    auto it = segments_by_start.upper_bound({p, 0});
    assert(it != segments_by_start.begin());
    auto [start, length] = *--it;
    int end = start + length;
    assert(start < p && p < end);  // guaranteed by problem statement!
    segments_by_start.erase({start, length});
    segments_by_length.erase({length, start});

    segments_by_start.insert({start, p - start});
    segments_by_length.insert({p - start, start});

    segments_by_start.insert({p, end - p});
    segments_by_length.insert({end - p, p});

    if (n > 0) cout << ' ';
    cout << segments_by_length.rbegin()->first;
  }
  std::cout << endl;
}
