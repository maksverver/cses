// Subarray Distinct Values
// https://cses.fi/problemset/task/2428
//
// Another solution using the two pointer technique: we move end index `j`
// through the array from left to right, and keep track of the start index `i`
// such that A[i..j) contains no more than K different values.
//
// We can use a std::map<> to count duplicates in the current range A[i..j).
// Incrementing `j` may add a value to the map, and then we may have to increase
// `i` accordingly until the number of entries is less than `K`.
//
// Time complexity: O(N log K)

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, K = 0;
  cin >> N >> K;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  int64_t answer = 0;
  int i = 0, j = 0;
  map<int, int> freq;  // freq[x] == number of occurrences of x in A[i:j)
  while (j < N) {
    ++freq[A[j++]];
    while (freq.size() > K) {
      auto it = freq.find(A[i++]);
      if (--it->second == 0) freq.erase(it);
    }
    answer += j - i;
  }

  cout << answer << '\n';
}
