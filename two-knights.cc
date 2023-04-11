#include <bits/stdc++.h>

using namespace std;

int64_t Calc(int64_t N) {
  assert(N > 0);
  if (N == 1) return 0;
  if (N == 2) return 6;
  if (N == 3) return 28;
  assert(N >= 4);

  int64_t S = N * N;
  int64_t total = 0;

  // +-------
  // | K . .
  // | . . x
  // | . x .
  total += (S - 3) * 4;

  // +--------
  // | . K . .
  // | . . . x
  // | x . x .
  total += (S - 4) * 8;

  // +--------
  // | . . . x
  // | . K . .
  // | . . . x
  // | x . x .
  total += (S - 5) * 4;

  // -----------
  //  . . K . .
  //  x . . . x
  //  . x . x .
  total += (S - 5) * (N - 4) * 4;

  // -----------
  //  x . . . x
  //  . . K . .
  //  x . . . x
  //  . x . x .
  total += (S - 7) * (N - 4) * 4;

  //  . x . x .
  //  x . . . x
  //  . . K . .
  //  x . . . x
  //  . x . x .
  total += (S - 9) * (N - 4) * (N - 4);

  return total / 2;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cout << Calc(i) << '\n';
  }
}
