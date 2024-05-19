#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;
int nums[N];

class MergeSortTree {
 private:
  vector<vector<int>> tree;
  int n;

  void merge(vector<int>& root, vector<int>& left, vector<int>& right) {
    int leftsz = (int) left.size(), rightsz = (int) right.size();
    int idxl = 0, idxr = 0;
    while (idxl < leftsz and idxr < rightsz) {
      if (left[idxl] <= right[idxr]) { 
        root.push_back(left[idxl]);
        idxl++;
      } else {
        root.push_back(right[idxr]);
        idxr++;
      }
    }
    while (idxl < leftsz) {
      root.push_back(left[idxl]);
      idxl++;
    }
    while (idxr < rightsz) {
      root.push_back(right[idxr]);
      idxr++;
    }
  }

  void build(int at, int b, int e) {
    if (b == e) {
      tree[at].push_back(nums[b]);
      return;
    }
    int mid = (b + e) >> 1;
    build(2 * at, b, mid);
    build(2 * at + 1, mid + 1, e);
    merge(tree[at], tree[2 * at], tree[2 * at + 1]);
  }

  int query(int at, int b, int e, int l, int r, int k) {
    if (r < b or e < l) return 0;
    if (l <= b and e <= r) {
      int cnt = upper_bound(tree[at].begin(), tree[at].end(), k) - tree[at].begin();
      return tree[at].size() - cnt;
    }
    int mid = (b + e) >> 1;
    int x = query(2 * at, b, mid, l, r, k);
    int y = query(2 * at + 1, mid + 1, e, l, r, k);
    return x + y;
  }

 public:
  MergeSortTree(int n) {
    this->n = n;
    tree.resize(4 * n, vector<int>());
    build(1, 1, n);
  }

  int query(int l, int r, int k) {
    return query(1, 1, n, l, r, k);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> nums[i];
    MergeSortTree mst(n);
    int q; cin >> q;
    while (q--) {
      int l, r, k; cin >> l >> r >> k;
      cout << mst.query(l, r, k) << '\n';
    }
  }
  return 0;
}

// problem link: https://www.spoj.com/problems/KQUERY/
