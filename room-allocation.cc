// Room allocation
// https://cses.fi/problemset/task/1164
//
// Similar to "Restaurant Customers": https://cses.fi/problemset/task/1619
// (see restaurant-customers.cc) except here we need to print room numbers too.
//
// Solution:
//
// Greedy algorithm. Process guests in order of arrival day (tie breaking rules
// don't matter), and assign them an existing room (if one is free) or else
// create a new one.
//
// If we keep the occupied rooms in a priority-queue sorted by date of departure
// (earliest on top), we can efficiently calculate the rooms that are freed
// up each day, before assigning them to newly arrived guests.
//
// Complexity: O(N log N) time, O(N) space.

#include <bits/stdc++.h>
#include <queue>

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

struct Guest {
  int index, arrival, departure;
};

bool operator<(const Guest &a, const Guest &b) {
  return a.arrival < b.arrival;
}

struct Occupation {
  int departure;
  int room;
};

// Compare by departure time, DESCENDING, so the top element in the priority
// queue is actually the occupation with the earliest departure date.
bool operator<(const Occupation &a, const Occupation &b) {
  return a.departure > b.departure;
}

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vector<Guest> guests(N);
  REP(i, N) guests[i].index = i;
  for (auto &[i, a, b] : guests) cin >> a >> b;

  std::sort(guests.begin(), guests.end());

  int room_count = 0;
  deque<int> rooms_available;
  priority_queue<Occupation> rooms_in_use;
  vector<int> answers(N, -1);
  for (auto [i, arrival, departure] : guests) {
    // Free up rooms of guests that have departed.
    while (!rooms_in_use.empty() && rooms_in_use.top().departure < arrival) {
      rooms_available.push_back(rooms_in_use.top().room);
      rooms_in_use.pop();
    }
    // Create a new room, if we have to.
    if (rooms_available.empty()) {
      rooms_available.push_back(++room_count);
    }
    int room = rooms_available.front();
    rooms_available.pop_front();
    answers[i] = room;
    rooms_in_use.push({.departure=departure, .room=room});
  }

  cout << room_count << '\n' << answers << endl;
}
