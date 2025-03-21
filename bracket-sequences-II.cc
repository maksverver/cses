// Bracket Sequences II
// https://cses.fi/problemset/task/2187

#include <bits/stdc++.h>

using namespace std;

namespace {

const int MOD = 1e9 + 7;

int Inverse(int i) {
  int res = 1, val = i;
  for (int e = MOD - 2; e > 0; e >>= 1) {
    if (e&1) res = int64_t{res} * val % MOD;
    val = int64_t{val} * val % MOD;
  }
  return res;
}

int Binomial(int n, int r) {
  int64_t res = 1;
  for (int i = n; i > r; --i) res = (res * i) % MOD;
  for (int i = n - r; i > 1; --i) res = (res * Inverse(i)) % MOD;
  return res;
}

static int solve_testdata[10][10] = {
  { 1,  1,  2,   5,   14,   42,   132,    429,   1430,    4862 },  // https://oeis.org/A000108     1*binomial(2n,   n-0)/(n+1)
  { 1,  2,  5,  14,   42,  132,   429,   1430,   4862,   16796 },  // https://oeis.org/A000108     2*binomial(2n+1, n-0)/(n+2)
  { 1,  3,  9,  28,   90,  297,  1001,   3432,  11934,   41990 },  // https://oeis.org/A000245     3*binomial(2n,   n-1)/(n+2)
  { 1,  4, 14,  48,  165,  572,  2002,   7072,  25194,   90440 },  // https://oeis.org/A002057     4*binomial(2n+1, n-1)/(n+3)
  { 1,  5, 20,  75,  275, 1001,  3640,  13260,  48450,  177650 },  // https://oeis.org/A000344     5*binomial(2n,   n-2)/(n+3)
  { 1,  6, 27, 110,  429, 1638,  6188,  23256,  87210,  326876 },  // https://oeis.org/A003517     6*binomial(2n+1, n-2)/(n+4)
  { 1,  7, 35, 154,  637, 2548,  9996,  38760, 149226,  572033 },  // https://oeis.org/A000588     7*binomial(2n,   n-3)/(n+4)
  { 1,  8, 44, 208,  910, 3808, 15504,  62016, 245157,  961400 },  // https://oeis.org/A003518     8*binomial(2n+1, n-3)/(n+5)
  { 1,  9, 54, 273, 1260, 5508, 23256,  95931, 389367, 1562275 },  // https://oeis.org/A001392     9*binomial(2n,   n-4)/(n+5)
  { 1, 10, 65, 350, 1700, 7752, 33915, 144210, 600875, 2466750 },  // https://oeis.org/A003519    10*binomial(2n+1, n-4)/(n+6)
};

// Solve() returns the number of ways to complete a bracket sequence prefix with
// nesting depth `d`, using `n` extra pairs of brackets (not counting the `d`
// closing brackets needed to finish the sequence).
//
// The formula (d + 1) * Binomial(2n + d, n) / (n + d + 1) was derived by
// calculating some values explicitly (see solve_testdata()) above, then finding
// the sequences in OEIS, then adjusting the formula a bit until it fit the data.
//
int Solve(int d, int n) {
  return int64_t{d + 1} * Binomial(2*n + d, n) % MOD * Inverse(n + d + 1) % MOD;
}

int Solve(int N, const string &S) {
  if (N % 2 != 0) return 0;

  int K = S.size();
  assert(K <= N);

  int depth = 0;
  for (char ch : S) {
    if (ch == '(') {
      ++depth;
    } else {
      assert(ch == ')');
      if (depth == 0) return 0;  // invalid bracket sequence
      --depth;
    }
  }

  if (N - K < depth) return 0;
  assert((N - K - depth) % 2 == 0);
  return Solve(depth, (N - K - depth) / 2);
}

}  // namespace

int main() {
  for (int x = 0; x < 10; ++x) {
    for (int n = 0; n < 10; ++n) {
      assert(Solve(x, n) == solve_testdata[x][n]);
    }
  }

  int N = 0;
  cin >> N;
  string S;
  cin >> S;

  cout << Solve(N, S) << endl;
}
