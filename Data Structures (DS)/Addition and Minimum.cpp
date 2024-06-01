#include <bits/stdc++.h>
using namespace std;

template<typename type> class SegmentTreeMin {
  struct Type {
    type mn, lazy;
    Type() : mn(0), lazy(0) {}
  };
  vector<Type> tree;
  int n;

  void propagate(int node, int begin, int end) {
    tree[node].mn += tree[node].lazy;
    if (begin != end) {
      tree[2 * node].lazy += tree[node].lazy;
      tree[2 * node + 1].lazy += tree[node].lazy;
    }
    tree[node].lazy = 0;
  }

  void update(int node, int begin, int end, int left, int right, type updateValue) {
    if (tree[node].lazy) propagate(node, begin, end);
    if (right < begin or end < left) return;
    if (left <= begin and end <= right) {
      tree[node].mn += updateValue;
      if (begin != end) {
        tree[2 * node].lazy += updateValue;
        tree[2 * node + 1].lazy += updateValue;
      }

      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, left, right, updateValue);
    update(2 * node + 1, mid + 1, end, left, right, updateValue);

    tree[node].mn = min(tree[2 * node].mn, tree[2 * node + 1].mn);
  }

  type query(int node, int begin, int end, int left, int right) {
    if (tree[node].lazy) propagate(node,  begin, end);
    if (right < begin or end < left) return INT_MAX;
    if (left <= begin and end <= right) return tree[node].mn;

    int mid = (begin + end) >> 1;
    type leftQuery = query(2 * node, begin, mid, left, right);
    type rightQuery = query(2 * node + 1, mid + 1, end, left, right);

    return min(leftQuery, rightQuery);
  }

public:

  SegmentTreeMin(int n) {
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
  SegmentTreeMin<long long> segmentTreeMin(n);
  while (m--) {
    int option; cin >> option;
    if  (option == 1) {
      int left, right, updateValue; cin >> left >> right >> updateValue;
      segmentTreeMin.update(left + 1, right, updateValue);
    } else {
      int left, right; cin >> left >> right;
      cout << segmentTreeMin.query(left + 1, right) << '\n';
    }
  }
  return 0;
}

// problem link: https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A