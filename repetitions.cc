#include <bits/stdc++.h>

using namespace std;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  std::string s;
  cin >> s;
  int max_run = 0;
  int i = 0;
  while (i < s.size()) {
    int j = i + 1;
    while (j < s.size() && s[i] == s[j]) ++j;
    max_run = std::max(max_run, j - i);
    i = j;
  }
  cout << max_run << endl;
}
