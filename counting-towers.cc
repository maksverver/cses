// Counting Towers
// https://cses.fi/problemset/task/2413
//
// Fun problem!
//
// Idea:
//
// Let's call a tower that has a 2-wide piece on top a type A tower, and a tower
// with to two 1-wide pieces on top a type B tower. Let a[n] be the number of
// type A towers of height n, and b[n] be the number of type B towers of height
// n.
//
// Then we have:
//
//  a[1] = 1
//  b[1] = 1
//
// because the only options for a height 1 tower are:
//
//  +--+--+    +--+--+
//  |     |    |  |  |
//  +-----+    +--+--+
//
// And we can calculate:
//
//   a[n + 1] = a[n] * 2 + b[n]
//
// Because for a type A tower, we can either extend the existing block or start
// a new one, but for a
//
//  +--+--+  +--+--+   +-----+
//  |     |  |     |   |     |
//  +--+--+  +     +   +--+--+
//  |     |  |     |   |  |  |
//     A        A         B
//
// And similarly:
//
//   b[n + 1] = a[n] + b[n] * 4
//
// Because the only options are:
//
//  +--+--+  +--+--+   +--+--+  +--+--+   +--+--+
//  |  |  |  |  |  |   |  |  |  |  |  |   |  |  |
//  +--+--+  +  +  +   +  +--+  +--+  +   +--+--+
//  |     |  |  |  |   |  |  |  |  |  |   |  |  |
//     A        B         B        B         B
//

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  constexpr int MOD = 1'000'000'007;

  int T = 0;
  cin >> T;
  while (T-- > 0) {
    int N = 0;
    cin >> N;

    int64_t last_a = 1;
    int64_t last_b = 1;

    REP(i, N - 1) {
      int64_t next_a = (last_a*2 + last_b)%MOD;
      int64_t next_b = (last_a + last_b*4)%MOD;

      last_a = next_a;
      last_b = next_b;
    }
    cout << (last_a + last_b)%MOD << '\n';
  }
}
