// Coin Piles
// https://cses.fi/problemset/task/1754
//
// Assume w.l.o.g. that A ≤ B. Then the problem is solvable if and only if
//
//   1) A + B is a multiple of 3
//   2) B ≤ 2A.
//
// Proof:
//
// Both conditions are clearly necessary:
//
//  1. each operation removes exactly 3 coins total, so the value of (A + B)
//     remains constant modulo 3. If that value is not 0 modulo 3, then we
//     cannot reach A = B = 0.
//  2. each operation removes at least 1 coin and at most 2 coins from each
//     pile, and when A or B reaches zero, we cannot continue. That means we
//     can remove at most 2A coins from B, so if B > 2A, B can never become
//     zero.
//
// Are they also sufficent? Yes.
//
// We can start by equalizing A and B, which takes X = B - A operations,
// leaving us with A' = B' = A - X = B - 2X. Since A' + B' = A' + A' = 0 mod 3,
// that means A' and B' are divisible by 3, and we can remove the remaining
// coins by alternating between the two operations.

#include <bits/stdc++.h>

using namespace std;

bool SolveCase() {
  int A = 0, B = 0;
  cin >> A >> B;
  if (A > B) std::swap(A, B);
  return (A + B) % 3 == 0 && B <= 2*A;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int T = 0;
  cin >> T;
  while (T-- > 0) cout << (SolveCase() ? "YES" : "NO") << '\n';
}
