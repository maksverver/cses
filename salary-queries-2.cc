// Salary Queries
// https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (int &a : A) cin >> a;

  ordered_set<pair<int, int>> s;  // set of {salary, person} pairs
  for (int i = 0; i < N; ++i) {
    s.insert({A[i], i + 1});
  }

  for (int q = 0; q < Q; ++q) {
    char ch = '\0';
    int x = 0, y = 0;
    cin >> ch >> x >> y;
    if (ch == '!') {
      s.erase({A[x - 1], x});
      s.insert({A[x - 1] = y, x});
    } else {
      cout << s.order_of_key({y + 1, 0}) - s.order_of_key({x, 0}) << '\n';
    }
  }
}
