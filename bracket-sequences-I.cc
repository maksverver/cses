// Bracket Sequences I
// https://cses.fi/problemset/task/2064
//
// The answer for 2n is the n-th Catalan number: https://en.wikipedia.org/wiki/Catalan_number

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

int Solve(int N) {
  if (N % 2 != 0) return 0;
  N /= 2;

  int64_t answer = 1;
  for (int i = N + 2; i <= 2*N; ++i) {
    answer = answer * i % MOD;
  }
  for (int i = 1; i <= N; ++i) {
    answer = answer * Inverse(i) % MOD;
  }
  return answer;
}

}  // namespace

int main() {
  int N = 0;
  cin >> N;
  cout << Solve(N) << endl;
}
