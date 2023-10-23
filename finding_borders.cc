// Finding Borders
// https://cses.fi/problemset/task/1732
//
// Solution: maintain a rolling hash of s[0:n] and s[N-n:N].
// See string-matching.cc for the principle.

#include <bits/stdc++.h>

using namespace std;

constexpr int64_t P = 37;
constexpr int64_t M = 36028797018963913;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  string S;
  cin >> S;

  bool first = true;
  int64_t hash_l = 0, hash_r = 0;
  int64_t multiplier = 1;  // invariant: multiplier == P^n % MOD
  for (int n = 0; n < S.size(); ++n) {
    if (n > 0 && hash_l == hash_r) {
      // Match found. Print length.
      if (!first) cout << ' ';
      first = false;
      cout << n;
    }

    // Update hashes.
    unsigned char ch_l = S[n];
    unsigned char ch_r = S[S.size() - 1 - n];
    hash_l = (hash_l*P + ch_l) % M;
    hash_r = (hash_r + ch_r * multiplier) % M;
    multiplier = (multiplier * P) % M;
  }
  cout << endl;
  assert(hash_l == hash_r);
}
