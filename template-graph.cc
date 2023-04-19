#include <bits/stdc++.h>

#if __has_include("dump.h")
#include "dump.h"
#else
#define DUMP(...)
#endif

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  REP(i, v.size()) {
    if (i > 0) os << ' ';
    os << v[i];
  }
  return os;
}

namespace {

int V, E;
vector<vector<int>> adj;

}  // namespace;

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  cin >> V >> E;
  adj.resize(V);
  REP(_, E) {
    int a = 0, b = 0;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int answer = -1;
  cout << answer << '\n';
}
