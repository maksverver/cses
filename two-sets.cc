// https://cses.fi/problemset/task/1092
//
// Logic:
//
// First, note that a solution is not possible if the sum of integers 1..N is
// odd, which happens for alternating pairs of values:
//
//   N:         1  2  3  4  5  6  7  8  9 10 11 12
//   sum:       1  3  6 10 15 21 28 36 45 55 66 78
//   possible:  N  N  Y  Y  N  N  Y  Y  N  N  Y  Y  (potentially)
//
// The sum is even whenever N is a multiple of 4, or a multiple of 4 minus 1.
// It's clear that a solution is impossible if the sum is odd. We just need to
// show that when the sum is even, a solution is possible.
//
// When N is a multiple of 4, then we can repeatedly pair up the largest and
// smallest numbers, creating an even number of pairs whose sums are all equal.
// Then we can simply assign half of the pairs to one set, and half to the
// other. Or viewed differently, we put both the lowest N/4 and highest N/4
// numbers in one set, and the remaining numbers in another.
//
// For example, N=12:
//
//   1 2 3  4 5 6  7 8 9  10 11 12
//   A A A  B B B  B B B   A  A  A
//
// A = [ 1,  2,  3, 10, 11, 12]  sum(A) = 18
// B = [ 4,  5,  6,  7,  8,  9]  sum(B) = 18
//
// When N is a multiple of 4 minus 1, we can do essentially the same but we
// pretend to have one extra, element 0. Again, we can pair up highest and
// lowest elements so that each pair has an equal sum, and again the number of
// pairs is even so we can assign half of them to each set, although we do not
// actually output 0.
//
// For example, N=11:
//
//   0 1 2  3 4 5  6 7 8  9 10 11
//   A A A  A B B  B B B  A  A  A
//
// A = [ 0,  1,  2,  9, 10, 11]  sum(A) = 33
// B = [ 3,  4,  5,  6,  7,  8]  sum(B) = 33
//

#include <bits/stdc++.h>

using namespace std;

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

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int64_t N = 0;
  cin >> N;

  if (N % 4 == 0 || N % 4 == 3) {
    cout << "YES\n";
    vector<int> A, B;
    for (int i = 1; i <= N; ++i) (i <= N/4 || i > 3*N/4 ? A : B).push_back(i);
    cout << A.size() << '\n';
    cout << A << '\n';
    cout << B.size() << '\n';
    cout << B << '\n';
  } else {
    cout << "NO\n";
  }
}
