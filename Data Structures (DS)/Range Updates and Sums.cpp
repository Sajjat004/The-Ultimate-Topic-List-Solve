#include <bits/stdc++.h>
using namespace std;

template<typename type> class SegmentTreeSum {
  struct Type {
    type sum, setValue, increment;
    bool setIsValid;

    Type() {
      sum = 0;
      setValue = 0;
      setIsValid = false;
    }
  };

  vector<Type> tree;
  int n;

  void propagate(int node, int begin, int end) {
    if (tree[node].setIsValid == true) {
      tree[node].sum = tree[node].setValue * (end - begin + 1);
    }

    tree[node].sum += tree[node].increment * (end - begin + 1);

    if (begin != end) {
      if (tree[node].setIsValid == true) {
        tree[2 * node].setIsValid = true;
        tree[2 * node].setValue = tree[node].setValue;
        tree[2 * node].increment = tree[node].increment;

        tree[2 * node + 1].setIsValid = true;
        tree[2 * node + 1].setValue = tree[node].setValue;
        tree[2 * node + 1].increment = tree[node].increment;
      }
      else {
        tree[2 * node].increment += tree[node].increment;
        tree[2 * node + 1].increment += tree[node].increment;
      }
    }

    if (tree[node].setIsValid == true) {
      tree[node].setIsValid = false;
      tree[node].setValue = 0;
      tree[node].increment = 0;
    }
    else {
      tree[node].increment = 0;
    }
  }

  void updateIncrement(int node, int begin, int end, int left, int right, type updateValue) {
    propagate(node, begin, end);

    if (right < begin or end < left) return;

    if (left <= begin and end <= right) {
      tree[node].sum += updateValue * (end - begin + 1);

      if (begin != end) {
        tree[2 * node].increment += updateValue;
        tree[2 * node + 1].increment += updateValue;
      }

      return;
    }

    int mid = (begin + end) >> 1;
    updateIncrement(2 * node, begin, mid, left, right, updateValue);
    updateIncrement(2 * node + 1, mid + 1, end, left, right, updateValue);

    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
  }

  void updateSet(int node, int begin, int end, int left, int right, type updateValue) {
    propagate(node, begin, end);

    if (right < begin or end < left) return;

    if (left <= begin and end <= right) {
      tree[node].sum = updateValue * (end - begin + 1);
      tree[node].setIsValid = false;
      tree[node].setValue = 0;
      tree[node].increment = 0;

      if (begin != end) {
        tree[2 * node].setIsValid = true;
        tree[2 * node].setValue = updateValue;
        tree[2 * node].increment = 0;

        tree[2 * node + 1].setIsValid = true;
        tree[2 * node + 1].setValue = updateValue;
        tree[2 * node + 1].increment = 0;
      }

      return;
    }

    int mid = (begin + end) >> 1;
    updateSet(2 * node, begin, mid, left, right, updateValue);
    updateSet(2 * node + 1, mid + 1, end, left, right, updateValue);

    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
  }

  type query(int node, int begin, int end, int left, int right) {

    propagate(node,  begin, end);

    if (right < begin or end < left) return 0;

    if (left <= begin and end <= right) return tree[node].sum;

    int mid = (begin + end) >> 1;
    type leftQuery = query(2 * node, begin, mid, left, right);
    type rightQuery = query(2 * node + 1, mid + 1, end, left, right);

    return leftQuery + rightQuery;
  }

public:

  SegmentTreeSum(int n) {
    this->n = n;
    tree.resize(4 * n);
  }

  void updateIncrement(int left, int right, type updateValue) {
    updateIncrement(1, 1, n, left, right, updateValue);
  }

  void updateSet(int left, int right, type updateValue) {
    updateSet(1, 1, n, left, right, updateValue);
  }

  type query(int left, int right) {
    return query(1, 1, n, left, right);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;

  SegmentTreeSum<long long> segmentTreeSum(n);
  for (int i = 1; i <= n; ++i) {
    int x; cin >> x;
    segmentTreeSum.updateSet(i, i, x);
  }

  while (m--) {
    int option; cin >> option;
    if (option == 1) {
      int left, right, updateValue; cin >> left >> right >> updateValue;
      segmentTreeSum.updateIncrement(left, right, updateValue);
    }
    else if (option == 2) {
      int left, right, updateValue; cin >> left >> right >> updateValue;
      segmentTreeSum.updateSet(left, right, updateValue);
    }
    else {
      int left, right; cin >> left >> right;
      cout << segmentTreeSum.query(left, right) << '\n';
    }
  }
  return 0;
}

// problem link: https://cses.fi/problemset/task/1735/