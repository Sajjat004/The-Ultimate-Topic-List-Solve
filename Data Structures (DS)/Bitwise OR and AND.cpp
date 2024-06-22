#include <bits/stdc++.h>
using namespace std;

template<typename type> class SegmentTreeSum {
  struct Type {
    type lazy, AND;
    Type() {
      lazy = 0;
      AND = 0;
    }
  };

  vector<Type> tree;
  int n;

  void propagate(int node, int begin, int end) {
    tree[node].AND |= tree[node].lazy;

    if (begin != end) {
      tree[2 * node].lazy |= tree[node].lazy;
      tree[2 * node + 1].lazy |= tree[node].lazy;
    }

    tree[node].lazy = 0;
  }

  void update(int node, int begin, int end, int left, int right, type updateValue) {
    if (tree[node].lazy) propagate(node, begin, end);

    if (right < begin or end < left) return;

    if (left <= begin and end <= right) {
      tree[node].AND |= updateValue;

      if (begin != end) {
        tree[2 * node].lazy |= updateValue;
        tree[2 * node + 1].lazy |= updateValue;
      }

      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, left, right, updateValue);
    update(2 * node + 1, mid + 1, end, left, right, updateValue);

    tree[node].AND = tree[2 * node].AND & tree[2 * node + 1].AND;
  }

  type query(int node, int begin, int end, int left, int right) {
    if (tree[node].lazy) propagate(node,  begin, end);

    if (right < begin or end < left) return (1 << 30) - 1;

    if (left <= begin and end <= right) return tree[node].AND;

    int mid = (begin + end) >> 1;
    type leftQuery = query(2 * node, begin, mid, left, right);
    type rightQuery = query(2 * node + 1, mid + 1, end, left, right);

    return leftQuery & rightQuery;
  }

public:

  SegmentTreeSum(int n) {
    this->n = n;
    tree.resize(4 * n);
  }

  void update(int left, int right, type updateValue) {
    update(1, 1, n, left, right, updateValue);
  }

  type query(int left, int right) {
    return query(1, 1, n, left, right);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  SegmentTreeSum<int> segmentTreeSum(n);
  while (m--) {
    int option; cin >> option;

    if  (option == 1) {
      int left, right, updateValue; cin >> left >> right >> updateValue;
      segmentTreeSum.update(left + 1, right, updateValue);
    }
    else {
      int left, right; cin >> left >> right;
      cout << segmentTreeSum.query(left + 1, right) << '\n';
    }
  }

  return 0;
}

// problem link: https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/C