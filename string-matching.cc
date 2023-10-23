// String Matching
// https://cses.fi/problemset/task/1753
//
// Use a rolling hash, e.g.
//
//   hash(s[i..j]) =
//      s[i]     * P^(j - i) +
//      s[i + 1] * P^(j - i - 1) +
//      s[i + 2] * P^(j - i - 2) +
//      ..
//      s[j - 2] * P^2 +
//      s[j - 1] * P^1 +
//      s[j]
//
// Where P is a small prime (I use 31).
//
// For example, hash("abc") = P^2*'a' + P*'b' + c = 961*'a' + 31*'b' + 'c';
//
// That way, we can efficiently extend the hash to the right:
//
//   hash(s[i..j+1]) = hash(s[i..j])*P + s[j + 1]
//
// And shrink from the left:
//
//   hash(s[i+1..j]) = hash(s[i..j]) - s[i]*P^(j - i - 1)
//
// These two operations allow sliding a window along the string to be searched
// and calculate the updated hash in O(1) time. I'm blindly assuming there are
// no hash collisions.
//
// This is similar to Rabin-Karp string searching.

#include <bits/stdc++.h>

using namespace std;

// P is a small prime used as the base.
// M is a large 55-bit prime (55 bit chosen so I can multiply with a byte
// without overflowing a 64-bit integer)
constexpr int64_t P = 37;
constexpr int64_t M = 36028797018963913;

int64_t Hash(string_view sv) {
  int64_t hash = 0;
  for (char ch : sv) hash = (hash*P + (unsigned char) ch) % M;
  return hash;
}

int CountOccurrences(const string &haystack, const string &needle) {
  if (haystack.size() < needle.size()) return 0;

  int64_t target = Hash(needle);
  int64_t hash = Hash(string_view(haystack.data(), needle.size()));

  int64_t multiplier = 1; // P^(|needle| - 1)
  for (int i = 1; i < needle.size(); ++i) multiplier = (multiplier * P) % M;

  int count = hash == target;
  for (int i = needle.size(); i < haystack.size(); ++i) {
    hash = (hash - multiplier * (unsigned char) haystack[i - needle.size()]) % M;
    if (hash < 0) hash += M;
    hash = (hash*P + (unsigned char) haystack[i]) % M;
    count += hash == target;
  }
  return count;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  string s, t;
  cin >> s >> t;
  cout << CountOccurrences(s, t) << '\n';
}
