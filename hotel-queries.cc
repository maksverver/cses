// Hotel Queries
// https://cses.fi/problemset/task/1143
//
// Solution:
//
// We can store the number of rooms in a segment tree that tracks the maximum of
// prefixes. Then we can use a search for a lower bound to find the index of the
// first hotel that has enough rooms available.

#include <bits/stdc++.h>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class S, class T> ostream& operator<<(ostream &os, const pair<S, T> &p) {
  return os << '{' << p.first << ',' << p.second << '}';
}

template<class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) os << (i ? " " : "") << v[i];
  return os;
}

template<typename V, typename C>
class SegmentTree {
public:
  SegmentTree(int size, V default_value, C combine)
      : size(size), layers(CountLayers(size)), data(((1 << layers) - 1), default_value),
        default_value(std::move(default_value)), combine(std::move(combine)) {}

  void Set(int i, V value) {
    assert(0 <= i && i < size);
    i = (1 << (layers - 1)) - 1 + i;
    data[i] = std::move(value);
    while (i > 0) {
      i = Parent(i);
      data[i] = combine(data[Child(i)], data[Child(i) + 1]);
    }
  }

  V Get(int i) const {
    assert(0 <= i && i < size);
    return data[(1 << (layers - 1)) - 1 + i];
  }

  // Returns the combined value over the range i..j (exclusive),
  // or default_value if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : default_value;
  }

  // Returns the least index `j` such that value <= GetRange(0, j), or if there
  // is no such value, returns `size` + 1 instead.
  //
  // Assumes values of GetRange(0, j) are ordered according to `compare`
  // (std::greater<V>() for sum and maximum, std::less<V>() for minimum, etc.)
  template<class Compare>
  int LowerBound(const V &value, const Compare &compare) const {
    if (compare(data[0], value)) return size + 1;  // value > GetRange(0, size)

    // Invariant: acc is the combined value from 0 to start (exclusive)
    V acc = default_value;
    int idx = 0, start = 0, end = 1 << (layers - 1);
    while (end - start > 1) {
      int mid = start + ((end - start) >> 1);
      V tmp = combine(acc, data[Child(idx)]);
      if (compare(tmp, value)) {  // tmp < value
        acc = std::move(tmp);
        start = mid;
        idx = Child(idx) + 1;
      } else {  // tmp >= value
        end = mid;
        idx = Child(idx);
      }
    }
    assert(end - start == 1);
    assert(!compare(combine(acc, data[idx]), value));  // acc + data[idx] >= value
    return start + compare(acc, value);
  }

  // Returns the least index `j` such that value < GetRange(0, j), or if there
  // is no such value, returns `size` + 1 instead.
  //
  // Let i = LowerBound(v) and j = UpperBound(v), then GetRange(0, k) = v for
  // all i <= k < j, and (j - i) is the number of prefixes that have a combined
  // value of exactly `v`.
  //
  // Assumes values of GetRange(0, j) are ordered according to `compare`
  // (std::greater<V>() for sum and maximum, std::less<V>() for minimum, etc.)
  template<class Compare>
  int UpperBound(const V &value, const Compare &compare) const  {
    if (!compare(value, data[0])) return size + 1;  // value >= GetRange(0, size)

    // Invariant: acc is the combined value from 0 to start (exclusive)
    V acc = default_value;
    int idx = 0, start = 0, end = 1 << (layers - 1);
    while (end - start > 1) {
      int mid = start + ((end - start) >> 1);
      V tmp = combine(acc, data[Child(idx)]);
      if (!compare(value, tmp)) {  // tmp <= value
        acc = std::move(tmp);
        start = mid;
        idx = Child(idx) + 1;
      } else {  // tmp > value
        end = mid;
        idx = Child(idx);
      }
    }
    assert(end - start == 1);
    assert(compare(value, combine(acc, data[idx])));  // acc + data[idx] > value
    return start + !compare(value, acc);
  }

private:
  static int Parent(int i) {
    return (i - 1) >> 1;
  }

  static int Child(int i) {
    return 2*i + 1;
  }

  static int CountLayers(int size) {
    int layers = size > 0;
    while (size > 1) {
      size = (size + 1) >> 1;
      ++layers;
    }
    return layers;
  }

  V GetRange(int i, int j, int idx, int start, int end) const {
    if (i <= start && j >= end) {
      return data[idx];
    }
    int mid = start + ((end - start) >> 1);
    if (j <= mid) {
      return GetRange(i, j, Child(idx), start, mid);
    }
    if (i >= mid) {
      return GetRange(i, j, Child(idx) + 1, mid, end);
    }
    return combine(
      GetRange(i, j, Child(idx), start, mid),
      GetRange(i, j, Child(idx) + 1, mid, end));
  }

  int size;
  int layers;
  vector<V> data;
  V default_value;
  C combine;
};

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
