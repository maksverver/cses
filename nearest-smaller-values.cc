// Nearest Smaller Values
// https://cses.fi/problemset/task/1645
//
// Solution:
//
// Let's go through the array from left to right. Suppose we are considering an
// index `k`: then we need to output the largest index `j` such that A[j] < A[k].
//
// Suppose that we keep the previous values in a vector {A[i], i} for 1 ≤ i < k.
// We can conclude that an element {A[i], i} is irrelevant if there is an index
// j, such that i < j < k and A[j] ≤ A[i]. After all: if for some future index k
// A[i] < A[k], then A[j] < A[k] too, and since j is greater it is preferred.
//
// That means we can discard all irrelevant elements. If we have a vector
// of pairs {A[i], i} sorted by i (strictly ascending), the values of relevant
// A[i]'s are strictly ascending!
//
// Now if we want to process an element {A[k], k}, we can first discard all
// {A[j], j} elements from the back of the vector where A[j] ≥ A[k], since these
// will have been made irrelevant by A[k]. Then, the remaining element {A[j], j}
// at the back of the vector (if there is any) will have A[j] < A[k] and we can
// output j, before appending {A[k], k}.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  // Stores pairs {A[i], i} ordered by `i`, such that there is no j > i
  // such that A[j] <= A[i]. Consequently, values of A[i] and i are both
  // strictly ascending!
  vector<pair<int, int>> value_index;

  int N = 0;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int a = 0;
    cin >> a;
    while (!value_index.empty() && value_index.back().first >= a) value_index.pop_back();
    int answer = value_index.empty() ? 0 : value_index.back().second;
    value_index.push_back({a, i});
    if (i > 1) cout << ' ';
    cout << answer;
  }
  cout << endl;
}
