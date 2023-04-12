// Playlist
// https://cses.fi/problemset/task/1141
//
// Logic:
//
// Let P[i] be the index of the previous time the i-th song played (i.e.,
// P[i] is the greatest index j < i such that A[i] = A[j]), or 0 if there is
// none.
//
// Consider A[1..j] (the prefix of A of length `j`). The length of the longest
// suffix of A[1..j] that contains no duplicates is j - max(P[i] for 1 ≤ i ≤ j),
// because any suffix that includes P[i] (1 ≤ i ≤ j) is not distinct, because
// it repeats A[i] == A[P[i]].
//
// Now we can simply run through the input one element at a time, calculate
// P[i] using a map that stores the last index by value, and tracking the
// maximum of P so far.
//
// This solution takes O(N log N) time and O(1) memory.

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  // We could also solve this without a map<>, by compressing song ids to the
  // range 0..N-1, then using a vector<> as a map.
  map<int, int> P;

  int N = 0;
  cin >> N;
  int max_P = 0, answer = 0;
  for (int i = 1; i <= N; ++i) {
    int id = 0;
    cin >> id;
    int &last_i = P[id];
    max_P = std::max(max_P, last_i);
    answer = std::max(answer, i - max_P);
    last_i = i;
  }
  cout << answer << '\n';
}
