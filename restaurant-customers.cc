// Restaurant customers
// https://cses.fi/problemset/task/1619

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  vector<pair<int, int>> v;
  while (N-- > 0) {
    int A = 0, B = 0;
    cin >> A >> B;
    v.push_back({A, +1});
    v.push_back({B, -1});
  }
  std::sort(v.begin(), v.end());

  int answer = 0, count = 0;
  for (auto [t, d] : v) {
    count += d;
    answer = std::max(answer, count);
  }
  cout << answer << endl;
}
