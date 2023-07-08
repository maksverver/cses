// List Removals
// https://cses.fi/problemset/task/1749
//
// Problem:
//
// Given a list of A of N integers, repeatedly remove the integer at a given
// index, and print the element removed.
//
// Solution:
//
// Use a Fenwick array where each element is 0 or 1 depending on whether the
// element is still present. Then we can use a lowerbound search to find the
// index i of the j-th remaining element (i.e., the prefix length i such that
// the sum has length j).

#include <bits/stdc++.h>

using namespace std;

static void fenwick_construct(std::vector<int> &a) {
  for (size_t i = 1; i < a.size(); i = 2 * i)
    for (size_t j = 2 * i - 1; j < a.size(); j += 2 * i)
      a[j] += a[j - i];
}

static size_t highest_bit(size_t num) {
  if (num) num = (unsigned long long)1 << (std::numeric_limits<unsigned long long>::digits - 1 - __builtin_clzll(num));
  return num;
}

/* Adds `v` to the value stored at index `i`. */
static void fenwick_update(std::vector<int> &a, size_t i, int v) {
  while (i < a.size()) a[i] += v, i |= i + 1;
}

/* Assuming all values are nonnegative, returns the least index `n` such that
   fenwick_prefixsum(a, n) >= sum, or returns a.size() + 1 if there is none.*/
static size_t fenwick_lowerbound(const std::vector<int> &a, int sum) {
  size_t n = 0;
  for (size_t bit = highest_bit(a.size()); bit; bit >>= 1) {
    if (n + bit <= a.size() && sum > a[n + bit - 1]) {
      sum -= a[n + bit - 1];
      n += bit;
    }
  }
  return n + (sum > 0);
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<int> present(N, 1);
  fenwick_construct(present);

  vector<int> answers;
  for (int n = 0; n < N; ++n) {
    int i = 0;
    cin >> i;
    int j = fenwick_lowerbound(present, i);
    if (n > 0) cout << ' ';
    cout << A[j - 1];
    fenwick_update(present, j - 1, -1);
  }
  cout << endl;
}
