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
    return query(1, 1, n, left, right);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, q; cin >> n >> q;
  vector <int> salary(n + 1, 0);
  vector<int> compress;
  for (int i = 1; i <= n; ++i) {
    cin >> salary[i];
    compress.push_back(salary[i]);
  }

  vector<array<int, 3>> query;
  for (int i = 1; i <= q; ++i) {
    char option; cin >> option;
    if (option == '!') {
      int updateIndex, updateValue; cin >> updateIndex >> updateValue;
      compress.push_back(updateValue);
      query.push_back({1, updateIndex, updateValue});
    } else {
      int left, right; cin >> left >> right;
      compress.push_back(left);
      compress.push_back(right);
      query.push_back({2, left, right});
    }
  }

  sort(compress.begin(), compress.end());
  compress.erase(unique(compress.begin(), compress.end()), compress.end());
  int limit = compress.size();

  SegmentTree segmentTree(limit);
  for (int i = 1; i <= n; ++i) {
    int updateIndex = upper_bound(compress.begin(), compress.end(), salary[i]) - compress.begin();
    segmentTree.update(updateIndex, 1);
  }

  for (auto [option, a, b] : query) {
    if (option == 1) {
      int updateIndex = upper_bound(compress.begin(), compress.end(), salary[a]) - compress.begin();
      segmentTree.update(updateIndex, -1);
      salary[a] = b;
      updateIndex = upper_bound(compress.begin(), compress.end(), salary[a]) - compress.begin();
      segmentTree.update(updateIndex, 1);
    } else {
      int left = upper_bound(compress.begin(), compress.end(), a) - compress.begin();
      int right = upper_bound(compress.begin(), compress.end(), b) - compress.begin();
      cout << segmentTree.query(left, right) << '\n';
    }
  }
  return 0;
}

// problem link: https://cses.fi/problemset/task/1144/