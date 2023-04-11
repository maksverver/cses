// Concert Tickets
// https://cses.fi/problemset/task/1091

// An alternative way to solve this problem is to use a std::multiset<>,
// but I thought that was too easy!
//
// See concert-tickets-2.cc for an alternate solutions without a
// std::priority_queue<> or other complex data structures!

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

struct Customer {
  int price = -1;
  int index = -1;
};

bool operator<(const Customer &a, const Customer &b) {
  return a.price < b.price;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0, M = 0;
  cin >> N >> M;
  vector<int> H(N);
  for (int &i : H) cin >> i;

  vector<Customer> C(M);
  REP(i, M) {
    cin >> C[i].price;
    C[i].index = i;
  }

  // Sort tickets by price, descending.
  std::sort(H.rbegin(), H.rend());

  // Sort customers by price, ascending.
  std::sort(C.begin(), C.end());

  // This priority queue contains indices of customers who are willing to buy
  // tickets at the last price, with the lowest index on top.
  priority_queue<int, vector<int>, greater<int>> indices;

  // The actual logic. We run through ticket prices from high to low,
  // selling them to the earliest customer that is willing to buy at this price.
  // Since we go down the prices, the set of eligible customers only increases.
  // Total runtime: O(N + M log M)
  vector<int> answers(M, -1);
  for (int price : H) {
    // Add indices of all customers willing to buy at `price` or less.
    while (!C.empty() && C.back().price >= price) {
      indices.push(C.back().index);
      C.pop_back();
    }
    // Sell the current ticket to the earliest potential customer, if there is one.
    if (!indices.empty()) {
      answers[indices.top()] = price;
      indices.pop();
    }
  }

  // Print out answers.
  for (int a : answers) cout << a << '\n';
}
