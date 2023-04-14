// Reading Books
// https://cses.fi/problemset/task/1631
//
// Fun easy problem :-)
//
// At first it seems like a complicated scheduling problem, but it turns out
// the answer is simply the max(sum(A), 2*max(A)).
//
// Rationale:
//
//  - each kid has to read all books, so the total time is at least sum(A)
//  - each book can be read by only one kid at a time, so the total time needed
//    is at least 2*A[i] for each book.
//
// This proves that max(sum(A), 2*max(A)) is a lower bound on the answer. But
// is it also enough? Yes. Let's define X = max(A) and Y = sum(A) - X: i.e.,
// X is the time it takes to read the first book, and Y the time to read all
// the others.
//
//  - if X ≥ Y, then one kid can reads the longest book, while the other reads
//    all the others; then they switch books, for a total of 2*X time.
//
//  - if X ≤ Y, then we can keep all the books in some order with X in first
//    position. One kid starts at position 1, the other at position 2, and
//    kids read books in order. Since the first kid is always X minutes behind
//    the second kid, and no book takes more than X minutes to finish, whenever
//    the first kid starts a new book, the second kid must have already finished
//    it. Similarly, when the first kid reaches the end of the sequence after
//    Y minutes, the second kid has finished the longest book (since X ≤ Y),
//    which the first kid still needs to read. So this takes X + Y = Y + X time
//    for both kids.

#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int64_t total = 0, longest = 0;
  int N = 0;
  cin >> N;
  while (N-- > 0) {
    int64_t a = 0;
    cin >> a;
    total += a;
    longest = std::max(longest, a);
  }

  cout << std::max(total, 2*longest) << endl;
}
