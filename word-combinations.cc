// Word Combinations
// https://cses.fi/problemset/task/1731
//
// Solution: dynamic programming + a trie.

#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

struct TrieNode {
  bool terminal = false;
  TrieNode *children[26] = {};
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  string S;
  cin >> S;

  int K = 0;
  cin >> K;
  vector<string> dictionary(K);
  for (string &s : dictionary) cin >> s;

  // Build the trie.
  TrieNode *root = new TrieNode;
  for (const string &s : dictionary) {
    TrieNode **node = &root;
    for (char ch : s) {
      assert('a' <= ch && ch <= 'z');
      node = &(*node)->children[ch - 'a'];
      if (!*node) *node = new TrieNode();
    }
    assert(!(*node)->terminal);
    (*node)->terminal = true;
  }

  // dp[i] is number of ways to construct the suffix of S starting at index i.
  vector<int> dp(S.size() + 1, 0);
  dp[S.size()] = 1;
  for (int i = S.size() - 1; i >= 0; --i) {
    TrieNode *node = root;
    for (int j = i; node; ++j) {
      if (node->terminal) dp[i] = (dp[i] + dp[j]) % MOD;
      if (j == S.size()) break;
      assert('a' <= S[j] && S[j] <= 'z');
      node = node->children[S[j] - 'a'];
    }
  }
  cout << dp[0] << endl;
}
