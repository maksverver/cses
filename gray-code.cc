// Gray Code
// https://cses.fi/problemset/task/2205
//
// Let f(n) be an array of 2^n Gray codes of length n, that starts with '0'^n
// and ends with '1' + '0'^(n-1). Then we can construct f(n+1) as:
//
//  f(n+1)[0] = '0' + f(n)[0]
//  f(n+1)[1] = '0' + f(n)[1]
//  ..
//  f(n+1)[2^(n-1) - 1] = '0' + f(n)[2^(n-1) - 1]
//  f(n+1)[2^(n-1)    ] = '1' + f(n)[2^(n-1) - 1]
//  f(n+1)[2^(n-1) + 0] = '1' + f(n)[2^(n-1) - 2]
//  ..
//  f(n+1)[2^n - 1] = '1' + f(n)[0]
//
// Some examples:
//
//  f(1)[0] = "0"
//  f(1)[1] = "1"
//
//  f(2)[0] = "00"
//  f(2)[1] = "01"
//  f(2)[2] = "11"
//  f(2)[3] = "10"
//
//  f(3)[0] = "000"
//  f(3)[1] = "001"
//  f(3)[2] = "011"
//  f(3)[3] = "010"
//  f(3)[7] = "110"
//  f(3)[6] = "111"
//  f(3)[5] = "101"
//  f(3)[4] = "100"
//
// etc.
//
//

#include <bits/stdc++.h>

using namespace std;

vector<string> Solve(int N) {
  assert(N > 0);
  if (N == 1) return {"0", "1"};

  vector<string> a = Solve(N - 1);
  vector<string> b;
  b.reserve(a.size() * 2);
  for (auto it = a.begin(); it != a.end(); ++it) b.push_back("0" + *it);
  for (auto it = a.rbegin(); it != a.rend(); ++it) b.push_back("1" + *it);
  return b;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;
  for (const string &s : Solve(N)) cout << s << '\n';
}
