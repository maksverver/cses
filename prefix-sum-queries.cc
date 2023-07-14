// Prefix Sum Queries
// https://cses.fi/problemset/task/2166
//
// Fun problem!
//
// Solution:
//
// Use a segment tree with a custom data type and combining function.
//
// We can calculate the maximum prefix sum of a subarray from the total sum
// and maximum prefix sum of two halves of the subarray. See Datum and Combine()
// defined below for details.

#include <bits/stdc++.h>

using namespace std;

struct Datum {
  int64_t sum;
  int64_t max_prefix_sum;

  static Datum single(int v) { return Datum{v, v > 0 ? v : 0};  }
};

static Datum Combine(const Datum &a, const Datum &b) {
  return Datum{
    .sum=a.sum + b.sum,
    .max_prefix_sum=max(a.max_prefix_sum, a.sum + b.max_prefix_sum)};
}

template<class V, class C>
class SegmentTree {
public:
  SegmentTree(int size, V zero, C combine)
      : size(size), layers(CountLayers(size)), data((1 << layers) - 1, zero),
        zero(std::move(zero)), combine(std::move(combine)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> SegmentTree(const std::vector<U> &v, V zero, C combine)
      : SegmentTree(v.size(), std::move(zero), std::move(combine)) {
    int k = (1 << (layers - 1)) - 1;
    for (int i = 0; i < v.size(); ++i) data[k + i] = v[i];
    for (int i = k - 1; i >= 0; --i) data[i] = combine(data[Child(i)], data[Child(i) + 1]);
  }

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
  // or zero if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : zero;
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
  V zero;
  C combine;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<Datum> A(N);
  for (int i = 0; i < N; ++i) {
    int a = 0;
    cin >> a;
    A[i] = Datum::single(a);
  }

  SegmentTree tree(A, Datum::single(0), Combine);

  while (Q--) {
    int type = 0, a = 0, b = 0;
    cin >> type >> a >> b;
    --a;
    if (type == 1) {
      tree.Set(a, Datum::single(b));
    } else {
      assert(type == 2);
      std::cout << tree.GetRange(a, b).max_prefix_sum << '\n';
    }
  }
}