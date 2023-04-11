#include <bits/stdc++.h>

using namespace std;

int main() {
  int N = 0;
  cin >> N;

  int res = 1;
  while (N-- > 0) res = res*2 % 1'000'000'007;
  cout << res << endl;
}
