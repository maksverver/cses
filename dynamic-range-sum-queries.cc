// Dynamic Range Sum Queries
// https://cses.fi/problemset/task/1648
//
// Solution: Fenwick array
//
// See also static-range-sum-queries.cc

#include <bits/stdc++.h>

using namespace std;

/* Converts a regular array into a Fenwick array (in linear time). */
static void fenwick_construct(std::vector<int64_t> &a) {
  for (size_t i = 1; i < a.size(); i = 2 * i)
    for (size_t j = 2 * i - 1; j < a.size(); j += 2 * i)
      a[j] += a[j - i];
}

/* Calculates the sum of the first `n` elements in `a` (which are the elements
   with zero-based indices strictly less than n). */
static int64_t fenwick_prefixsum(const std::vector<int64_t> &a, size_t n) {
  int64_t res = 0;
  while (n > 0) res += a[n - 1], n &= n - 1;
  return res;
}

/* Calculates the sum of elements from index i to j (exclusive). */
static int64_t fenwick_rangesum(const std::vector<int64_t> &a, size_t i, size_t j) {
  return i < j ? fenwick_prefixsum(a, j) - fenwick_prefixsum(a, i) : 0;
}

/* Adds `v` to the value stored at index `i`. */
static void fenwick_update(std::vector<int64_t> &a, size_t i, int v) {
  while (i < a.size()) a[i] += v, i |= i + 1;
}

/* Retrieves the value stored at index `i`. */
static int fenwick_retrieve(const std::vector<int64_t> &a, size_t i) {
  int res = a[i];
  for (size_t bit = 1; i & bit; bit += bit) res -= a[i ^ bit];
  return res;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int64_t> A(N);
  for (auto &x : A) cin >> x;

  fenwick_construct(A);

  while (Q--) {
    int t = 0;
    cin >> t;
    if (t == 1) {
      int i = 0, x = 0;
      cin >> i >> x;
      --i;
      fenwick_update(A, i, x - fenwick_retrieve(A, i));
    }
    if (t == 2) {
      int a = 0, b = 0;
      cin >> a >> b;
      cout << fenwick_rangesum(A, a - 1, b) << '\n';
    }
  }
}
