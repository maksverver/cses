#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int64_t N = 0;
  cin >> N;
  cout << N;
  while (N != 1) {
    N = N % 2 == 0 ? N / 2 : 3*N + 1;
    cout << ' ' << N;
  }
  cout << endl;
}
