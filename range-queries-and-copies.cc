// Range Queries and Copies
// https://cses.fi/problemset/task/1737
//
// Solution: copy-on-write segment tree.

#include <bits/stdc++.h>
#include <memory>

using namespace std;

class SegmentTree {
public:
  explicit SegmentTree(int value)
      : size(1), value(value), left(nullptr), right(nullptr) {}

  SegmentTree(shared_ptr<SegmentTree> left, shared_ptr<SegmentTree> right)
      : size(left->size + right->size), value(left->value + right->value),
        left(left), right(right) {}

  static shared_ptr<SegmentTree> Construct(const vector<int> &A) {
    vector<shared_ptr<SegmentTree>> trees;
    for (int a : A) trees.push_back(make_shared<SegmentTree>(a));
    while (trees.size() > 1) {
      vector<shared_ptr<SegmentTree>> next_trees;
      for (int i = 0; i < trees.size(); i += 2) {
        if (i + 2 <= trees.size()) {
          next_trees.push_back(make_shared<SegmentTree>(trees[i], trees[i + 1]));
        } else {
          next_trees.push_back(trees[i]);
        }
      }
      next_trees.swap(trees);
    }
    return trees.at(0);
  }

  shared_ptr<SegmentTree> Assign(int i, int v) {
    if (size == 1) {
      assert(i == 0);
      return make_shared<SegmentTree>(v);
    } else if (i < left->size) {
      return make_shared<SegmentTree>(left->Assign(i, v), right);
    } else {
      return make_shared<SegmentTree>(left, right->Assign(i - left->size, v));
    }
  }

  int64_t GetRange(int a, int b) const {
    if (b <= 0 || a >= size) return 0;
    if (a <= 0 && b >= size) return value;
    int k = left->size;
    return left->GetRange(a, b) + right->GetRange(a - k, b - k);
  }

private:
  int size;
  int64_t value;
  shared_ptr<SegmentTree> left, right;
};

int main() {
  // Make C++ I/O not slow. It's sad that this is necessary :-(
  ios_base::sync_with_stdio(false), cin.tie(nullptr);

  int N = 0, Q = 0;
  cin >> N >> Q;

  vector<int> A(N);
  for (auto &x : A) cin >> x;

  vector<shared_ptr<SegmentTree>> trees;
  trees.push_back(SegmentTree::Construct(A));

  while (Q--) {
    int type = 0, i = 0;
    cin >> type >> i;
    --i;
    if (type == 1) {
      int a = 0, x = 0;
      cin >> a >> x;
      --a;
      trees[i] = trees.at(i)->Assign(a, x);
    } else if (type == 2) {
      int a = 0, b = 0;
      cin >> a >> b;
      --a;
      cout << trees.at(i)->GetRange(a, b) << '\n';
    } else {
      assert(type == 3);
      trees.push_back(trees.at(i));
    }
  }
}
