// Nested Ranges Count
// https://cses.fi/problemset/task/2168
//
// Variation of nested-ranges-count.cc that uses a Fenwick tree to count
// values. (See codelib2/Fenwick.cpp for more information.)

#include <bits/stdc++.h>

using namespace std;


/* Calculates the sum of the first `n` elements in `a` (which are the elements
   with zero-based indices strictly less than n). */
static int fenwick_prefixsum(std::vector<int> &a, size_t n) {
  int res = 0;
  while (n > 0) res += a[n - 1], n &= n - 1;
  return res;
}

/* Calculates the sum of elements from index i to j (exclusive). */
static int fenwick_rangesum(std::vector<int> &a, size_t i, size_t j) {
  return i < j ? fenwick_prefixsum(a, j) - fenwick_prefixsum(a, i) : 0;
}

/* Adds `v` to the value stored at index `i`. */
static void fenwick_update(std::vector<int> &a, size_t i, int v) {
  while (i < a.size()) a[i] += v, i |= i + 1;
}


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

  // Compress coordinates into range 0..M-1
  int M = 0;
  {
    map<int, int> m;
    for (auto [x, y, i]: ranges) {
      m[x] = 0;
      m[y] = 0;
    }
    for (auto &[k, v] : m) v = M++;
    for (auto &[x, y, i]: ranges) {
      x = m[x];
      y = m[y];
    }
  }

  sort(ranges.begin(), ranges.end());

  vector<int> contained(N);
  {
    vector<int> fenwick_tree(M);
    for (auto [x, y, i] : ranges) {
      // Range [x:y] is contained by all ranges that end at y2 >= y.
      contained[i] += fenwick_rangesum(fenwick_tree, y, M);
      fenwick_update(fenwick_tree, y, 1);
    }
  }

  std::reverse(ranges.begin(), ranges.end());

  vector<int> contains(N);
  {
    vector<int> fenwick_tree(M);
    for (auto [x, y, i] : ranges) {
      // Range [x:y] contains all ranges that end at y2 <= y.
      contains[i] += fenwick_prefixsum(fenwick_tree, y + 1);
      fenwick_update(fenwick_tree, y, 1);
    }
  }

  cout << contains << '\n';
  cout << contained << '\n';
}
