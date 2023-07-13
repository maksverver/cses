// Range Updates and Sums
// https://cses.fi/problemset/task/1735
//
// Solution: Lazy Segment Tree

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = int(a), _end_##i = int(b); i < _end_##i; ++i)
#define REP(i,n) FOR(i,0,n)

enum class MutationType { NONE, SET, ADD };

template<class V> class Mutation {
public:
  Mutation() : type(MutationType::NONE) {}

  MutationType Type() const { return type; }
  const V &Value() const { return value; }

  Mutation &Set(V v) {
    type = MutationType::SET;
    value = std::move(v);
    return *this;
  }

  Mutation &Add(V v) {
    if (type == MutationType::NONE) {
      type = MutationType::ADD;
      value = std::move(v);
    } else {
      value += std::move(v);
    }
    return *this;
  }

  Mutation &Apply(const Mutation &m) {
    return
      m.type == MutationType::SET ? Set(m.value) :
      m.type == MutationType::ADD ? Add(m.value) :
      *this;
  }

  V ExtractValue() {
    type = MutationType::NONE;
    return std::move(value);
  }

private:
  MutationType type;
  V value;
};

template<typename V>
class LazySegmentTree {
public:
  // Initialize an empty segment tree of given size.
  LazySegmentTree(int size, V zero)
      : size(size), layers(CountLayers(size)),
        data((1 << layers) - 1, zero),
        mutations((1 << layers) - 1),
        zero(std::move(zero)) {}

  // Initialize a segment tree from a vector of given size.
  template<class U> LazySegmentTree(const std::vector<U> &v, V zero)
      : LazySegmentTree(v.size(), std::move(zero)) {
    int k = (1 << (layers - 1)) - 1;
    for (int i = 0; i < v.size(); ++i) data[k + i] = v[i];
    for (int i = k - 1; i >= 0; --i) data[i] = data[Child(i)] + data[Child(i) + 1];
  }

  // Returns the value at index i.
  V Get(int i) const {
    return GetRange(i, i + 1);
  }

  // Returns the sum of elements in range i..j (exclusive), or zero if i >= j.
  V GetRange(int i, int j) const {
    assert(0 <= i && j <= size);
    return i < j ? GetRange(i, j, 0, 0, 1 << (layers - 1)) : zero;
  }

  void Add(int i, const V &value) {
    AddRange(i, i + 1, value);
  }

  void Set(int i, const V &value) {
    SetRange(i, i + 1, value);
  }

  // Add `value` to all elements in range i..j (exclusive); does nothing if i >= j.
  void AddRange(int i, int j, const V &value) {
    assert(0 <= i && j <= size);
    if (i < j) UpdateRange(i, j, 0, 0, 1 << (layers - 1), Mutation<V>().Add(value));
  }

  // Assign `value` to all elements in range i..j (exclusive); does nothing if i >= j.
  void SetRange(int i, int j, const V &value) {
    assert(0 <= i && j <= size);
    if (i < j) UpdateRange(i, j, 0, 0, 1 << (layers - 1), Mutation<V>().Set(value));
  }

private:
  enum UpdateType { NONE, SET, ADD };

  static int Parent(int i) { return (i - 1) >> 1; }
  static int Child(int i) { return 2*i + 1; }

  static int CountLayers(int size) {
    int layers = size > 0;
    while (size > 1) {
      size = (size + 1) >> 1;
      ++layers;
    }
    return layers;
  }

  void ClearUpdate(int idx, int width) const {
    Mutation<V> &m = mutations[idx];
    if (m.Type() == MutationType::NONE) return;

    if (width > 1) {
      mutations[Child(idx) + 0].Apply(m);
      mutations[Child(idx) + 1].Apply(m);
    }

    if (m.Type() == MutationType::SET) {
      data[idx] = m.ExtractValue() * width;
    } else {
      assert(m.Type() == MutationType::ADD);
      data[idx] += m.ExtractValue() * width;
    }
  }

  V GetRange(int i, int j, int idx, int start, int end) const {
    ClearUpdate(idx, end - start);
    if (i <= start && j >= end) return data[idx];
    int mid = start + ((end - start) >> 1);
    V result = zero;
    if (i < mid) result += GetRange(i, j, Child(idx) + 0, start, mid);
    if (j > mid) result += GetRange(i, j, Child(idx) + 1, mid, end);
    return result;
  }

  void UpdateRange(int i, int j, int idx, int start, int end, const Mutation<V> &m) {
    if (i <= start && j >= end) {
      mutations[idx].Apply(m);
    } else {
      ClearUpdate(idx, end - start);
      int mid = start + ((end - start) >> 1);
      if (i < mid) UpdateRange(i, j, Child(idx) + 0, start, mid, m);
      if (j > mid) UpdateRange(i, j, Child(idx) + 1, mid, end, m);
      ClearUpdate(Child(idx) + 0, mid - start);
      ClearUpdate(Child(idx) + 1, end - mid);

      data[idx] = data[Child(idx)] + data[Child(idx) + 1];
    }
  }

  int size;
  int layers;
  mutable vector<V> data;
  mutable vector<Mutation<V>> mutations;
  V zero;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> A(N);
  for (auto &a : A) cin >> a;
  LazySegmentTree<int64_t> tree(A, 0);

  while (Q--) {
    int type = 0, a = 0, b = 0;;
    cin >> type >> a >> b;
    --a;
    if (type == 1 || type == 2) {
      int x = 0;
      cin >> x;
      if (type == 1) {
        tree.AddRange(a, b, x);
      } else {
        tree.SetRange(a, b, x);
      }
    } else {
      assert(type == 3);
      cout << tree.GetRange(a, b) << '\n';
    }
  }
}
