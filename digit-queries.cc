// Digit queries
// https://cses.fi/problemset/task/2431
//
// Problem: consider the decimal representation of the natural numbers,
// concatenated into a single string ("123456789101112..."). Return the
// digits at given positions in the string.
//
// The string is the concatenation of:
//
//  - 9 numbers of length 1 (9 characters)
//  - 90 numbers of length 2 (2×90 = 180 characters)
//  - 900 numbers of length 3 (3×900 = 2700 characters)
// etc.
//
// Each of these form sections where numbers have equal lengths. We can go
// through the lengths to find the section we're in, then easily compute
// the number we're taking a digit from. Time complexity: O(log K) per query,
// or O(N log K) overall.
//
// In theory we could optimize this into an O(N + log K) solution by sorting
// queries and precomputing powers of 10 for the final division, but it's not
// worth the effort (and I didn't account for the time to sort the queries).

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int Calc(int64_t K) {
  assert(K > 0);
  --K;  // make index zero-based
  int len = 1;
  int64_t first = 1;  // fist number of length `len`
  int64_t count = 9;  // count of numbers with length `len`
  while (len*count <= K) {
    K -= len*count;
    len += 1;
    first *= 10;
    count *= 10;
  }

  // Which number we are taking the digit from.
  int64_t number = K / len + first;

  // Index of the digit in `number` we return, counting from the right.
  int pos = (len - 1) - K % len;

  // Extract digit at index `pos`.
  while (pos-- > 0) number /= 10;
  assert(number > 0);
  return number % 10;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int Q = 0;
  cin >> Q;
  while(Q--) {
    int64_t K = 0;
    cin >> K;
    cout << Calc(K) << '\n';
  }
}
