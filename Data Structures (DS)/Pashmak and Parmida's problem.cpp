#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  vector<int> tree;
  vector<int> nums;
  int n;

  void update(int node, int begin, int end, int updateIndex, int updateValue) {
    if (updateIndex > end or updateIndex < begin) return;
    if (begin == end) {
      tree[node] += updateValue;

      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, updateIndex, updateValue);
    update(2 * node + 1, mid + 1, end, updateIndex, updateValue);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  int query(int node, int begin, int end, int left, int right) {
    if (end < left or begin > right) return 0;
    if (left <= begin and end <= right) return tree[node];

    int mid = (begin + end) >> 1;
    int x = query(2 * node, begin, mid, left, right);
    int y = query(2 * node + 1, mid + 1, end, left, right);

    return x + y;
  }
public:
  SegmentTree(int n) {
    this->n = n;
    this->nums = nums;
    tree.assign(4 * n, 0);
  }

  void update(int updateIndex, int updateValue) {
    update(1, 1, n, updateIndex, updateValue);
  }

  int query(int left, int right) {
    if (left > right) return 0;

    return query(1, 1, n, left, right);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> nums(n + 1);
  for (int i = 1; i <= n; ++i) cin >> nums[i];
  map<int, int> mmap;
  vector<int> left(n + 1);
  for (int i = 1; i <= n; ++i) {
    mmap[nums[i]]++;
    left[i] = mmap[nums[i]];
  }

  mmap.clear();
  vector<int> right(n + 1);
  for (int i = n; i >= 1; --i) {
    mmap[nums[i]]++;
    right[i] = mmap[nums[i]];
  }

  long long ans = 0;
  SegmentTree segmentTree(n);

  for (int i = 1; i <= n; ++i) {
    ans += segmentTree.query(right[i] + 1, n);
    segmentTree.update(left[i], 1);
  }
  cout << ans << '\n';
  return 0;
}

// problem link: https://codeforces.com/contest/459/problem/D
