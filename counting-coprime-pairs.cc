// Counting Coprime Pairs
// https://cses.fi/problemset/task/2417
//
// Solution:
//
// We can map each input number a[i] to a set of distinct prime factors (without
// multiplicity; e.g. 10, 50, and 100 all have the set {2, 5} of prime factors).
// These sets are relatively small: at most 7 elements (since a[i] <= 1e6, and
// 2*3*5*7*11*13*17*19 > 1e6). Two numbers are coprime iff. the intersection of
// their factors is empty.
//
// For each input number, we can use inclusion-exclusion to count how many
// previous numbers share at least one factor.

#include <bits/stdc++.h>

using namespace std;

// factor[i] == 0 if i is prime, or else factor[i] is a prime factor of i.
static vector<int> factor;

static vector<int> DistinctFactors(int x) {
  vector<int> r;
  while (factor[x] != 0) {
    int p = factor[x];
    r.push_back(p);
    while (x % p == 0) x /= p;
  }
  if (x > 1) r.push_back(x);
  return r;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  // Sieve of Eratosthenes to find prime factors
  factor = vector<int>(*ranges::max_element(A) + 1);
  for (int p = 2; p*p < factor.size(); ++p) if (factor[p] == 0) {
    for (int q = p*p; q < factor.size(); q += p) if (factor[q] == 0) {
      factor[q] = p;
    }
  }

  int64_t answer = 0;
  unordered_map<int, int> count;
  for (int a : A) {
    vector<int> factors = DistinctFactors(a);
    vector<int> signs(1 << factors.size());
    vector<int> products(1 << factors.size());
    signs[0] = -1;
    products[0] = 1;
    for (int i = 0; i < factors.size(); ++i) {
      for (int m = 0; m < (1 << i); ++m) {
        signs[m | (1 << i)] = -signs[m];
        products[m | (1 << i)] = products[m] * factors[i];
      }
    }
    for (int m = 0; m < products.size(); ++m) {
      answer -= signs[m] * count[products[m]];
    }
    for (int x : products) count[x]++;
  }
  cout << answer << endl;
}
