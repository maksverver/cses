// Distinct Values Queries
// https://cses.fi/problemset/task/1734
//
// Solution 1: Mo's algorithm.
//
// Time complexity: O(N + Q × N × sqrt(N))

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

// Given a vector of length N with K distinct integers, maps the integers to
// a compact range of integers 0 and K (exclusve), and returns K.
static int Compress(vector<int> &values) {
  unordered_map<int, int> index_by_value;
  for (int &v : values) {
    int &i = index_by_value[v];
    if (i == 0) i = index_by_value.size();
    v = i - 1;
  }
  return index_by_value.size();
}

struct Query {
  int a, b, index;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<Query> queries(Q);
  REP(i, Q) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a;
    queries[i] = Query{.a = a, .b = b, .index=i};
  }

  int K = Compress(A);
  int sqrtN = sqrt(N);

  sort(queries.begin(), queries.end(), [sqrtN](const Query &q, const Query &r) {
    return tuple(q.a / sqrtN, q.b) < tuple(r.a / sqrtN, r.b);
  });

  vector<int> answers(Q);
  vector<int> count(K);
  int i = 0, j = 0, distinct = 0;
  for (auto [a, b, index] : queries) {
    while (j < b) if (count[A[j++]]++ == 0) ++distinct;
    while (i > a) if (count[A[--i]]++ == 0) ++distinct;
    while (j > b) if (--count[A[--j]] == 0) --distinct;
    while (i < a) if (--count[A[i++]] == 0) --distinct;
    answers[index] = distinct;
  }

  for (int a : answers) cout << a << '\n';
}
