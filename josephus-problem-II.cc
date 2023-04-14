// Josephus Problem II
// https://cses.fi/problemset/task/2163
//
// Solution: if we consider the array A with integers 1 through N, it's easy to
// calculate the positions to be deleted as i_0 = k % N, i_1 = (i0 + K) % (N - 1),
// .. i_k = (i_(k-1) + K) % (N - k) etc. However, deleting elements from an array
// takes linear time. So instead, we will store the values in a tree structure
// which allows efficient removal at an arbitrary index in O(log N) time.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Node {
  int size = 0;   // 1 for leaf, 1+ for interior node
  int value = 0;  // 0 for interior node, 1+ for leaf node
  struct Node *left = nullptr, *right = nullptr;
};

constexpr int Size(Node *node) {
  return node ? node->size : 0;
}

// Remove the i-th value from the subtree rooted at `node`.
int Remove(Node *node, int i) {
  assert(0 <= i && i < node->size);
  --node->size;
  return node->value > 0 ? node->value :
    i < Size(node->left) ?
        Remove(node->left, i) :
        Remove(node->right, i - Size(node->left));
}

Node *CreateNodes(int i, int j) {
  assert(i < j);
  if (j - i == 1) return new Node{.size=1, .value=i + 1};
  int k = i + (j - i)/2;
  Node *left = CreateNodes(i, k);
  Node *right = CreateNodes(k, j);
  return new Node{.size=j-i, .left=left, .right=right};
}

int main() {
  int N = 0, K = 0;
  cin >> N >> K;

  Node *root = CreateNodes(0, N);

  bool first = true;
  int pos = 0;
  while (N > 0) {
    pos = (pos + K) % N--;

    if (first) first = false; else cout << ' ';
    cout << Remove(root, pos);
  }
  cout << '\n';

  // Note: memory allocated by CreateNodes() is leaked here!
}
