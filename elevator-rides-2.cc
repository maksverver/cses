// Elevator Rides
// https://cses.fi/problemset/task/1653
//
// Bin packing. Given an array A of size N, partition it into a minimal number
// of subsets, such that the sum of each subset is less than or equal to X.
//
// Variation of elevator-rides.cc that uses recursion with memoization, which
// maybe makes the logic a little more obvious?
//
// The idea is that for each subset, we calculate the minimum number of parts,
// and for that number of parts, the minimum sum of the smallest part.
//
// To calculate these values for a given subset s, we go over all the elements
// x in the subset: one of them has to belong to the smallest part. That means
// it either forms a part by itself, or it was added to the smallest part of
// the subset s\x (s without x).
//
// Initially this seemed counter-intuitive: if we have a subset s\x with part
// sizes p1 < p2 < p3 < .., isn't it possible that p2 < p1 + x < p3? i.e.,
// after adding x to p1, it is no longer in the smallest part! Yes this is
// possible, but then x would not be in the smallest part of s either. If x is
// part of the smallest part in s, then it was certainly added to the smallest
// part in s\x.

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

constexpr unsigned Bit(int i) { return 1u << i; }

int N, X;
vector<int> A;

struct Result {
  int min_parts;
  int last_size;
};

bool operator<(const Result &a, const Result &b) {
  return std::tie(a.min_parts, a.last_size) < std::tie(b.min_parts, b.last_size);
}

static Result memo[1 << 20];

// Returns: minimum number of parts, minimum part size
Result Calc(unsigned m) {
  if (m == 0) return {0, X};

  Result &mem = memo[m];
  if (mem.min_parts >= 0) return mem;

  Result res = {N, X};
  REP(i, N) if (m & Bit(i)) {
    Result prev = Calc(m - Bit(i));
    prev.last_size += A[i];
    if (prev.last_size > X) {
      prev.min_parts++;
      prev.last_size = A[i];
    }
    res = min(res, prev);
  }
  return mem = res;
}

int main() {
  cin >> N >> X;
  A.resize(N);
  for (auto &x : A) cin >> x;

  memset(memo, -1, sizeof(memo));
  cout << Calc(Bit(N) - 1).min_parts << endl;
}
