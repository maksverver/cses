// Array Description
// https://cses.fi/problemset/task/1746
//
// f(index, value) -> number of ways to end a sequence at `index` with value `value`
//
// f(1, x) = 1 if A[i] == x or A[i] == 0
// f(1, x) = f(i - 1, x - 1) + f(i - 1, x) + f(i - 1, x + 1) if A[i] == 0 or A[i] = x else 0
//

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

constexpr int MOD = 1'000'000'007;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<int64_t> prev(M + 1), next;
  for (int x = 1; x <= M; ++x) prev[x] = A[0] == 0 || A[0] == x ? 1 : 0;
  for (int i = 1; i < N; ++i) {
    next.assign(M + 1, 0);
    for (int x = 1; x <= M; ++x) if (A[i] == 0 || x == A[i]) {
      next[x] = prev[x] + (x > 1 ? prev[x - 1] : 0) + (x < M ? prev[x + 1] : 0);
      next[x] %= MOD;
    }
    next.swap(prev);
  }

  int64_t answer = 0;
  for (int a : prev) answer += a;
  answer %= MOD;

  cout << answer << '\n';
}
