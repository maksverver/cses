#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int64_t N = 0;
  cin >> N;
  int64_t sum = N * (N + 1) / 2;
  for (int i = 0; i < N - 1; ++i) {
    int x = 0;
    cin >> x;
    sum -= x;
  }
  cout << sum << endl;
}
