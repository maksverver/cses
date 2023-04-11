// Creating strings
// https://cses.fi/problemset/task/1622

// Problem: Generate all permutations of a string, in lexicographical order.
//
// Solution: There are at least two different ways to solve this problem.
// One is to iterate over the permutations (which I've implemented here),
// the other is to recursively generate possible strings from the available
// characters.
//
// Both of these solutions take O(M) time to generate M strings, while it
// takes O(N×M) to print all of them (N being the length of the strings).

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

void ReverseSuffix(string &s, int i) {
  for (int j = s.size() - 1; i < j; ++i, --j) {
    std::swap(s[i], s[j]);
  }
}

// Transforms `s` into the next larger permutation and returns true,
// or if we are at the largest permutation, transforms `s` into the
// smallest permutation and returns false.
//
// This is basically what std::next_permutation() does, but I wanted to
// implement it myself for fun.
bool NextPermutation(string &s) {
  int i = s.size() - 1;
  while (i > 0 && s[i - 1] >= s[i]) --i;
  if (i > 0) {
    // At this poinst, s[i - 1] < s[i], and the suffix s[i:] is in nonincreasing
    // order. To transform into the next permutation, we will swap s[i - 1] with
    // the smallest character in the suffix that is still larger than s[i - 1],
    // and then reverse the suffix.
    int j = i;
    while (j + 1 < s.size() && s[j + 1] > s[i - 1]) ++j;
    std::swap(s[i - 1], s[j]);
  }
  ReverseSuffix(s, i);
  return i > 0;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  string s;
  cin >> s;

  // Start with the minimal permutation.
  sort(s.begin(), s.end());

  // Cycle through all permutations without printing to count how many there are.
  int count = 0;
  do ++count; while (NextPermutation(s));
  cout << count << '\n';

  // If everything is correct, we should be back where we started.
  assert(std::is_sorted(s.begin(), s.end()));

  // Print all permutations.
  do cout << s << '\n'; while (NextPermutation(s));
}
