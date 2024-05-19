#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class SegmentTree {
  vector<ll> tree;
  vector<int> nums;
  int n;

  void build(int node, int begin, int end) {
    if (begin == end) {
      tree[node] = nums[begin];

      return;
    }
    int mid = (begin + end) >> 1;
    build(2 * node, begin, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  void update(int node, int begin, int end, int updateIndex, int updateValue) {
    if (updateIndex > end or updateIndex < begin) return;
    if (begin == end) {
      tree[node] = updateValue;

      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, updateIndex, updateValue);
    update(2 * node + 1, mid + 1, end, updateIndex, updateValue);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  ll query(int node, int begin, int end, int left, int right) {
    if (end < left or begin > right) return 0;
    if (left <= begin and end <= right) return tree[node];

    int mid = (begin + end) >> 1;
    ll x = query(2 * node, begin, mid, left, right);
    ll y = query(2 * node + 1, mid + 1, end, left, right);

    return x + y;
  }
public:
  SegmentTree(int n, vector<int>& nums) {
    this->n = n;
    this->nums = nums;
    tree.assign(4 * n, 0);
    build(1, 1, n);
  }

  void update(int updateIndex, int updateValue) {
    update(1, 1, n, updateIndex, updateValue);
  }

  ll query(int left, int right) {
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
      cout << segmentTree.query(++left, right) << '\n';
    }
  }
  return 0;
}

// Problem Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A