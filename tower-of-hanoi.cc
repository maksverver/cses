// Tower of Hanoi
// https://cses.fi/problemset/task/2165
//
// Solution: recursion. To move a stack of height N from stack A to C using B
// as temporary space,we must first move the top N-1 from A to B, then the
// 1 bottom disk from A to C, then the remaining N-1 disks from B to C using A
// as temporary space.
//
// Call the number of moves necessary to move N disks f(N). Then f(0) = 0,
// f(N) = 2×f(N - 1) + 1, so that f(1)=1, f(2)=3, f(3)=7, ... f(N) = 2^N - 1.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

void Move(int n, int from, int temp, int to) {
  if (n == 0) return;
  Move(n - 1, from, to, temp);
  cout << from << ' ' << to << '\n';
  Move(n - 1, temp, from, to);
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  cout << (int64_t{1} << N) - 1 << '\n';
  Move(N, 1, 2, 3);
}
