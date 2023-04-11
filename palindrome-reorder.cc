// Palindrome Reorder
// https://cses.fi/problemset/task/1755

// Solution approach: a string can be rearranged into a palindrome if and only
// if there is at most one character that occurs an odd number of times. So we
// can start by counting the frequency of each character to determine if a
// solution is possible.
//
// If there is 1 character with odd frequency, then we will put it in the center
// and the resulting string has odd length. Otherwise, the string will have even
// length. Either way, the remaining characters are placed pairwise around the
// center character.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  std::string S;
  std::getline(std::cin, S);
  int N = S.size();

  int count[26] = {};
  for (char ch : S) count[ch - 'A']++;

  int odd = 0;
  for (int i : count) odd += i % 2;

  if (odd > 1) {
    cout << "NO SOLUTION" << std::endl;
  } else {
    int i = 0;
    REP(j, 26) {
      if (count[j] % 2 == 1) {
        S[N/2] = (char) ('A' + j);
      }
      REP(k, count[j] / 2) {
        S[i] = S[N - 1 - i] = (char) ('A' + j);
        ++i;
      }
    }
    cout << S << endl;
  }
}
