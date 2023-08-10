// Increasing Array Queries
// https://cses.fi/problemset/task/2416
//
// Solution:
//
// To make a subarray A[i:j] nondecreasing with the minimum number of operations,
// we should only increment an element if it is less than its predecessor.
//
// Let A(i,j) be the subarray A[i..j].
// Let B(i,j) be the minimal nondecreasing version of A(i, j).
// Then B(i,j)[k] = max(A(i, j)[i], A(i,j)[i + 1], .. A(i,j)[k]).
// Let C(i,j)[k] be the amount added at index k: C(i, j)[k] = B(i,j)[k] - A(i,j)[k].
//
// It's clear that A(i,j)[k] doesn't depend on the bounds i or j, so we can
// just write it A(i,j)[k] = A[k]. The value of B(i,j)[k] and therefore C(i,j)[k]
// only depends on the values of B(i,j) to the left of k, so we can write
// B(i,j)[k] = B(i)[k], and C(i,j)[k] = C(i)[k].
//
// Now we can implement the following algorithm:
//
//   1. First, we group the queries by left endpoint, i.
//   2. Then we construct values C(N-1), C(N-2), .. C(0) incrementally.
//
// If we store C in a segment tree, we can efficiently update and query it.
// To answer the queries (i, j) we use the segment tree to get the sum of
// C(i)[i..j].
//
// This leaves the question of how to update C(i) from C(i + 1).
//
// Imagine that we have constructed B(i+1) and C(i+1). Then B(i+1) is a
// nondecreasing sequence. We can compress the representation into segments
// of equal values, but even better, we can identify those segments by the
// indices in A. For example: indices {3, 6, 10} represent the array
// B={A[3], A[3], A[3], A[6], A[6], A[6], A[6], A[10], ... }
//
// In the source code below, these indices are stored in a vector `indices`
// where the lowest value is at the back of the vector, which is a bit confusing,
// but it allows us to efficiently add and remove the lowest values.
//
// When extending C(i+1) to C(i), we must add A[i] in front. We replace the
// indices j where A[i] > A[j], and update the values of C(i) in the segment
// tree.
//
// Take the sample input with the minimal sorted suffixes are:
//
//        0   1  2  3  4
//   A = [2, 10, 4, 2, 5]
//                           indices
//  B(4):               5    4           C(4):              0
//  B(3):            2  5    3, 4        C(3):           0  0
//  B(2):         4  4  5    2, 4        C(2):        0  2  0
//  B(1):     10 10 10 10    1           C(1):     0  6  8  5
//  B(0):   2 10 10 10 10    0, 1        C(0):  0  0  6  8  5
//
// The overall algorithm requires O(N) space and O(N log N) time.

#include <bits/stdc++.h>

#include "lazy-segment-tree.h"

using namespace std;

struct Query {
  int index, begin, end;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (int &a : A) cin >> a;
  vector<Query> queries(Q);
  for (int q = 0; q < Q; ++q) {
    queries[q].index = q;
    cin >> queries[q].begin >> queries[q].end;
    --queries[q].begin;
  }
  std::ranges::sort(queries, [](const Query &a, const Query &b) {
    return a.begin < b.begin;
  });

  auto add = [](int64_t a, int64_t b) { return a + b; };
  LazySegmentTree added(N, int64_t{0}, add);

  vector<int> indices;
  vector<int64_t> answers(Q, -1);
  int q = Q - 1;
  for (int i = N - 1; i >= 0; --i) {
    while (!indices.empty() && A[indices.back()] <= A[i]) {
      int begin = indices.back();
      indices.pop_back();
      int end = indices.empty() ? N : indices.back();
      if (A[begin] < A[i]) added.AddRange(begin, end, A[i] - A[begin]);
    }
    indices.push_back(i);

    while (q >= 0 && queries[q].begin == i) {
      auto &query = queries[q--];
      answers[query.index] = added.GetRange(query.begin, query.end);
    }
  }
  assert(q == -1);

  for (const auto &a : answers) cout << a << '\n';
}
