// Fibonacci Numbers
// https://cses.fi/problemset/task/1722
//
// Given the definition of Fibonacci numbers:
//
//  F(0) = 0
//  F(1) = 1
//  F(i) = F(i - 1) + F(i - 2)
//
// Define a 2x2 matrix to calculate F(i) from F(i - 1) and F(i - 2):
//
//   [ 1 1 ] [ F(i-1) ] = [ F(i-1) + F(i-2) ] = [ F(i)   ]
//   [ 1 0 ] [ F(i-2) ] = [ F(i-1)          ] = [ F(i-1) ]
//
// To calculate F(i) efficiently, we can raise that matrix to the i-th power:
//
//   [ 1 1 ]^(i-1)   [ 1 ] = [ F(i)   ]
//   [ 1 0 ]       × [ 0 ] = [ F(i-1) ]
//
// This can be calculated in O(log i) time using exponentation by squaring.

#include <bits/stdc++.h>

using namespace std;

namespace {

const int MOD = 1e9 + 7;

using Mat2x2 = std::array<std::array<int64_t, 2>, 2>;

const Mat2x2 one = {
  1, 0,
  0, 1 };

const Mat2x2 fib = {
  1, 1,
  1, 0 };

Mat2x2 operator*(const Mat2x2 &a, const Mat2x2 &b) {
  return Mat2x2{
      (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % MOD,
      (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % MOD,
      (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % MOD,
      (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % MOD,
  };
}

Mat2x2 pow(Mat2x2 mat, int64_t e) {
  Mat2x2 res = one;
  while (e > 0) {
    if (e & 1) res = res * mat;
    mat = mat * mat;
    e >>= 1;
  }
  return res;
}

}  // namespace

int main() {
  int64_t N = -1;
  cin >> N;
  assert(N >= 0);
  cout << pow(fib, N)[0][1] << endl;
}
