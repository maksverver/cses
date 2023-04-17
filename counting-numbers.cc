// Counting Numbers
// https://cses.fi/problemset/task/2220
//
// Classic dynamic programming / recursion with memoization.
//
// We can recursively construct a number between A and B from left to right,
// tracking whether the upper- and lower-bounds still apply. The count of
// remaining numbers depends only on the last digit and which bounds apply,
// so we can memoize this to avoid enumerating all numbers explicitly.
//
// Note that we must be careful to allow duplicate leading zeroes!

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

constexpr int MAX_DIGITS = 19;

// Digits of input A and B from most-significant to least-significant
static int digits_A[MAX_DIGITS];
static int digits_B[MAX_DIGITS];

static int64_t memo[MAX_DIGITS][2][2][11];

int64_t Calc(int pos, bool lo_bound, bool hi_bound, bool leading_zeros, int last_digit) {
  if (pos == MAX_DIGITS) return 1;
  int64_t &m = memo[pos][lo_bound][hi_bound][leading_zeros ? 10 : last_digit];
  if (m >= 0) return m;
  int64_t res = 0;
  int min_d = lo_bound ? digits_A[pos] : -1;
  int max_d = hi_bound ? digits_B[pos] : 10;
  FOR(d, (lo_bound ? min_d : 0), (hi_bound ? max_d + 1 : 10)) {
    if (d != last_digit || (leading_zeros && d == 0)) {
      res += Calc(pos + 1, d == min_d, d == max_d, leading_zeros && d == 0, d);
    }
  }
  return m = res;
}

int main() {
  int64_t A = 0, B = 0;
  cin >> A >> B;

  REP(i, MAX_DIGITS) digits_A[MAX_DIGITS - 1 - i] = A % 10, A /= 10;
  REP(i, MAX_DIGITS) digits_B[MAX_DIGITS - 1 - i] = B % 10, B /= 10;

  memset(memo, -1, sizeof(memo));
  cout << Calc(0, true, true, true, 0) << endl;
}
