// Apartments
// https://cses.fi/problemset/task/1084
//
// Solution: greedy algorithm.
//
// Start by sorting values of A and B. Then the solution is as follows:
//
//  1. If the first tenant can fits in the first building (abs(A[0] - B[0]) <= K)
//     then we assign tenant 0 to building 0 and continue with the remaining
//     tenants and buildings.
//  2. Otherwise, if A[0] < B[0], it is optimal to drop the tenant, because if
//     they can't fit in B[0] they can't fit in any bigger buildings either.
//  3. Otherwise, B[0] <= A[0], and it is optimal to drop building, because if
//     A[0] doesn't fit in building 0, none of the tenants that require more
//     space will.
//
// Step 2 and 3 should be fairly obvious. It remains to be shown that step 1
// is optimal. We can prove it by contradiction. Suppose that we could assign
// the first tenant to the first building, but there is an optimal solution were
// we don't do that. Then in that better solution one of four cases apply:
//
//   1. Tenant 0 and building 0 are unassigned: in this case we can still
//      assign tenant 0 to building 0 to create an even better solution,
//      contradicting the assumption that the solution was optimal.
//   2. Tenant 0 is assigned to a different building j while building 0 is
//      unassigned: then we can assign tenant 0 to building 0 instead and the
//      solution is just as good.
//   3. Tenant 0 is unassigned but building 0 has a different tenant i:
//      then we can change the tenant from i to 0 and the solution is just as
//      good.
//   4. Tenant 0 is assigned to building j and building 0 is assigned to
//      tenant i: then we can swap the assignments so that tentant 0 is
//      assigned building 0, and tenant i to building j.
//
//      (This works because given A[0] <= A[i] and B[0] <= B[i], it can be
//      proven that if abs(A[i] - B[0]) <= K and abs(A[0] - B[j]) <= K,
//      then abs(A[0] - B[0]) <= K and abs(A[i] - B[i]) <= K. I won't prove
//      that here in detail.)
//
// In every case we can generate a solution that assigned tenant 0 to building
// 0 that is just as good or even better (case 1), which proves that there is no
// better solution than assigning assigning tenant 0 to building 0 whevever we
// can.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0, K = 0;
  cin >> N >> M >> K;
  vector<int> A(N), B(M);
  for (int &a : A) cin >> a;
  for (int &b : B) cin >> b;

  std::sort(A.begin(), A.end());
  std::sort(B.begin(), B.end());

  int answer = 0, i = 0, j = 0;
  while (i < N && j < M) {
    if (abs(A[i] - B[j]) <= K) {
      // Assign i-th tenant to j-th building.
      ++answer;
      ++i;
      ++j;
    } else if (A[i] < B[j]) {
      // Skip i-th tenant: if they can't fit in the j-th building, they can't
      // fit in any other either.
      ++i;
    } else {
      // Skip the j-th building: if even the least-demanding tenant doesn't fit
      // in this building, nobody does.
      ++j;
    }
  }
  cout << answer << endl;
}
