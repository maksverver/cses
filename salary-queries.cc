// Salary Queries
// https://cses.fi/problemset/task/1144
//
// Solution: compress salaries into a compact range, then use a Fenwick array
// where indices correspond with salaries, and values with number of people with
// that salary, so we can do a range query to find the number of people within
// a given salary range.
//
// See also salary-queries-2.cc for a version using an ordered set.

#include <bits/stdc++.h>

#include "fenwick.h"

using namespace std;

struct Query {
  char ch;
  int x, y;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &a : A) cin >> a;

  vector<Query> queries(Q);
  for (auto &[ch, x, y] : queries) cin >> ch >> x >> y;

  // Compress all salary values into a contiguous range between 0 and N+2Q.
  map<int, int> salary_to_index;
  {
    vector<int> distinct = A;
    for (const auto &[ch, x, y] : queries) {
      if (ch == '!') {
        distinct.push_back(y);
      } else {
        assert(ch == '?');
        distinct.push_back(x);
        distinct.push_back(y);
      }
    }
    std::sort(distinct.begin(), distinct.end());
    distinct.erase(std::unique(distinct.begin(), distinct.end()), distinct.end());
    for (size_t i = 0; i < distinct.size(); ++i) {
      salary_to_index[distinct[i]] = i;
    }
  }

  vector<int> count(salary_to_index.size());
  for (int &a : A) {
    a = salary_to_index.at(a);
    count[a]++;
  }
  fenwick_construct(count);
  for (const auto &[ch, x, y] : queries) {
    if (ch == '!') {
      int &a = A[x - 1];
      fenwick_update(count, a, -1);
      a = salary_to_index.at(y);
      fenwick_update(count, a, +1);
    } else {
      assert(ch == '?');
      cout << fenwick_rangesum(count, salary_to_index.at(x), salary_to_index.at(y) + 1) << '\n';
    }
  }
}
