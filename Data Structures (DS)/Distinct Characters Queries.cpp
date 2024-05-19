#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  vector<vector<bool>> tree;
  int n;
  string s;
  void build(int node, int begin, int end) {
    if (begin == end) {
      tree[node][s[begin - 1] - 'a'] = true;

      return;
    }

    int mid = (begin + end) >> 1;
    build(2 * node, begin, mid);
    build(2 * node + 1, mid + 1, end);

    for (int i = 0; i < 26; ++i) {
      tree[node][i] = tree[2 * node][i] | tree[2 * node + 1][i];
    }
  }

  void update(int node, int begin, int end, int updateIndex, char updateValue) {
    if (begin > updateIndex or end < updateIndex) return;
    if (begin == end) {
      tree[node][s[begin - 1] - 'a'] = false;
      s[begin - 1] = updateValue;
      tree[node][s[begin - 1] - 'a'] = true;

      return;
    }

    int mid = (begin + end) >> 1;
    update(2 * node, begin, mid, updateIndex, updateValue);
    update(2 * node + 1, mid + 1, end, updateIndex, updateValue);

    for (int i = 0; i < 26; ++i) {
      tree[node][i] = tree[2 * node][i] | tree[2 * node + 1][i];
    }
  }

  vector<bool> query(int node, int begin, int end, int left, int right) {
    if (right < begin or end < left) return vector<bool> (26, false);
    if (left <= begin and end <= right) return tree[node];

    int mid = (begin + end) >> 1;
    vector<bool> x = query(2 * node, begin, mid, left, right);
    vector<bool> y = query(2 * node + 1, mid + 1, end, left, right);
    vector<bool> ans(26, false);
    for (int i = 0; i < 26; ++i) ans[i] = x[i] | y[i];

    return ans;
  }
public:
  SegmentTree(int n, const string& s) {
    this->s = s;
    this->n = n;
    tree.resize(4 * n, vector<bool>(26, false));
    build(1, 1, n);
  }

  void update(int updateIndex, int updateValue) {
    update(1, 1, n, updateIndex, updateValue);
  }

  int query(int left, int right) {
    vector<bool> ans = query(1, 1, n, left, right);
    int count = 0;
    for (bool x : ans) count += (x == true);
    return count;
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s; cin >> s;
  int n = s.size();
  SegmentTree segmentTree(n, s);

  int q; cin >> q;
  while (q--) {
    int option; cin >> option;
    if (option == 1) {
      int updateIndex; cin >> updateIndex;
      char updateValue; cin >> updateValue;
      segmentTree.update(updateIndex, updateValue);
    } else {
      int left, right; cin >> left >> right;
      cout << segmentTree.query(left, right) << '\n';
    }
  }
  return 0;
}

// problem link: https://codeforces.com/problemset/problem/1234/D