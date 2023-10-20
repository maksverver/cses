// Creating Strings II
// https://cses.fi/problemset/task/1715
//
// Solution:
//
// The number of ways to reorder a string of length n that consists of `a` a's,
// `b` b's, etc., is n! / a! / b! / c! / .. / z!
//
// Logic: n! is the number of permutations of the string if all elements were
// different. a! is the number of ways to reorder the a's, b! the number of ways
// to reorder the b's, etc.

#include "mod-int.h"

#include <bits/stdc++.h>

using namespace std;

using MI = ModInt<int32_t, int64_t, (int32_t)(1e9 + 7)>;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  string s;
  cin >> s;

  vector<MI> fac = {1};
  while (fac.size() <= s.size()) fac.push_back(fac.back() * fac.size());

  MI answer = fac[s.size()];
  int counts[26] = {};
  for (char ch : s) {
    assert('a' <= ch && ch <= 'z');
    ++counts[ch - 'a'];
  }
  for (int c : counts) answer /= fac[c];
  cout << answer << '\n';
}
