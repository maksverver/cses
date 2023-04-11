// Concert Tickets
// https://cses.fi/problemset/task/1091
//
// An alternative way to solve this problem, using no standard data structures
// like std::multiset<> or std::priority_queue<>.
//
// What's the complexity of this solution? I'm not quite sure!

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;

  // Read ticket prices and sort.
  vector<int> H(N);
  for (int &i : H) cin >> i;
  std::sort(H.begin(), H.end());

  // P[i] is the highest index of a ticket with a price no greater than H[i].
  // When P[i] == i, the i-th ticket itself is still unsold. Otherwise,
  // P[i] < i, and P[i] points to an earlier ticket that may or may not be sold.
  vector<int> P(N);
  REP(i, N) P[i] = i;

  vector<int> stack;  // declared outside so we can reuse its memory

  REP(i, M) {
    int max_price = 0;
    cin >> max_price;

    // Find most expensive ticket that we could buy (which may be already sold).
    int j = std::upper_bound(H.begin(), H.end(), max_price) - H.begin() - 1;

    // Now find an unsold ticket no more expensive. We will do this by following
    // the P[i] pointers to previous tickets until we reach an unsold one, then
    // afterwards we update the pointers visited with the final index. This is
    // similar to implementing a disjoint-set datastructure with path
    // compression!
    while (j >= 0 && P[j] != j) {
      stack.push_back(j);
      j = P[j];
    }
    while (!stack.empty()) {
      P[stack.back()] = j;
      stack.pop_back();
    }

    if (j < 0) {
      // No answer.
      cout << -1 << '\n';
    } else {
      // Buy j-th ticket and mark it as sold.
      cout << H[j] << '\n';
      P[j] = j - 1;
    }
  }
}
