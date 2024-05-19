#include <bits/stdc++.h>
using namespace std;

struct Node {
  int minimum;
  int totalMinumum;
  Node() {
    minimum = INT_MAX;
    totalMinumum = 0;
  }

  Node operator+ (Node const& object) {
    Node ans;
    ans.minimum = object.minimum;
    ans.totalMinumum = totalMinumum + object.totalMinumum;

    return ans;
  }
};

class SegmentTree {
  vector<Node> tree;
  vector<int> nums;
  int n;

  void build(int node, int begin, int end) {
    if (begin == end) {
      tree[node].minimum = nums[begin];
      tree[node].totalMinumum = 1;
      return;
    }
    int mid = (begin + end) >> 1;
    build(2 * node, begin, mid);
    build(2 * node + 1, mid + 1, end);

    if (tree[2 * node].minimum < tree[2 * node + 1].minimum) {
      tree[node] = tree[2 * node];
    } else if(tree[2 * node].minimum > tree[2 * node + 1].minimum) {
      tree[node] = tree[2 * node + 1];
    } else {
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void update(int node, int begin, int end, int updateIndex, int updateValue) {
    if (updateIndex > end or updateIndex < begin) return;
    if (begin == end) {
      tree[node].minimum = updateValue;
      tree[node].totalMinumum = 1;
      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, updateIndex, updateValue);
    update(2 * node + 1, mid + 1, end, updateIndex, updateValue);

    if (tree[2 * node].minimum < tree[2 * node + 1].minimum) {
      tree[node] = tree[2 * node];
    } else if(tree[2 * node].minimum > tree[2 * node + 1].minimum) {
      tree[node] = tree[2 * node + 1];
    } else {
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  Node query(int node, int begin, int end, int left, int right) {
    if (end < left or begin > right) return Node();
    if (left <= begin and end <= right) return tree[node];

    int mid = (begin + end) >> 1;
    Node x = query(2 * node, begin, mid, left, right);
    Node y = query(2 * node + 1, mid + 1, end, left, right);

    if (x.minimum < y.minimum) {
      return x;
    } else if (x.minimum > y.minimum) {
      return y;
    } else {
      return x + y;
    }
  }
public:
  SegmentTree(int n, vector<int>& nums) {
    this->n = n;
    this->nums = nums;
    tree.resize(4 * n);
    build(1, 1, n);
  }

  void update(int updateIndex, int updateValue) {
    update(1, 1, n, updateIndex, updateValue);
  }

  Node query(int left, int right) {
    return query(1, 1, n, left, right);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector <int> nums(n + 1, 0);
  for (int i = 1; i <= n; ++i) cin >> nums[i];
  SegmentTree segmentTree(n, nums);

  while (m--) {
    int option; cin >> option;
    if (option == 1) {
      int index, value; cin >> index >> value;
      segmentTree.update(++index, value);
    } else {
      int left, right; cin >> left >> right;
      Node ans = segmentTree.query(++left, right);
      cout << ans.minimum << " " << ans.totalMinumum  << '\n';
    }
  }
  return 0;
}

// problem link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C