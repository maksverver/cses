#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  int prev = 0;
  cin >> prev;
  int64_t answer = 0;
  for (int i = 1; i < N; ++i) {
    int next = 0;
    cin >> next;
    if (next < prev) answer += prev - next; else prev = next;
  }
  cout << answer << endl;
}
