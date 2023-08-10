// Hotel Queries
// https://cses.fi/problemset/task/1143
//
// Solution:
//
// We can store the number of rooms in a segment tree that tracks the maximum of
// prefixes. Then we can use a search for a lower bound to find the index of the
// first hotel that has enough rooms available.

#include <bits/stdc++.h>

#include "segment-tree.h"

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> avail;

  auto max = [](int a, int b) { return a > b ? a : b; };
  SegmentTree<int, decltype(max)> tree(N, 0, max);

  REP(hotel, N) {
    int rooms = 0;
    cin >> rooms;
    tree.Set(hotel, rooms);
  }

  REP(m, M) {
    if (m > 0) cout << ' ';

    int people = 0;
    cin >> people;

    int hotel = tree.LowerBound(people, std::less<int>());
    assert(hotel > 0);
    if (hotel > N) {
      cout << 0;
    } else {
      int rooms = tree.Get(hotel - 1);
      assert(rooms >= people);
      tree.Set(hotel - 1, rooms - people);
      cout << hotel;
    }
  }
  cout << endl;
}
