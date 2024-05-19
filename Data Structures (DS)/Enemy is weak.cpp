#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

class SegTree {
  int n;
  vector<int> tree;
public:
  SegTree(int n) {
    this->n = n;
    tree.assign(4 * (n + 2), 0);
  }

  void update(int at, int b, int e, int idx, int val) {
    if (idx < b or idx > e) return;
    if (b == e) {
      tree[at] += val;
      return;
    }
    int mid = (b + e) >> 1;
    update(2 * at, b, mid, idx, val);
    update(2 * at + 1, mid + 1, e, idx, val);
    tree[at] = tree[2 * at] + tree[2 * at + 1];
  }

  int query(int at, int b, int e, int l, int r) {
    if (r < b or e < l) return 0;
    if (l <= b and e <= r) return tree[at];
    int mid = (b + e) >> 1;
    int x = query(2 * at, b, mid, l, r);
    int y = query(2 * at + 1, mid + 1, e, l, r);
    return x + y;
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    vector<int> v(n);
    set<int> s;
    for (int& x : v) {
      cin >> x;
      s.insert(x);
    }
    map<int, int> id;
    int cnt = 0;
    for (int x : s) id[x] = ++cnt;
    for (int& x : v) x = id[x];
    SegTree segtree1(cnt);
    SegTree segtree2(cnt);
    for (int x : v) {
      segtree1.update(1, 1, cnt, x, 1);
    }
    long long ans = 0;
    for (int i = n - 1; i >= 0; --i) {
      int x = segtree2.query(1, 1, n, 1, v[i] - 1);
      int y = segtree1.query(1, 1, n, v[i] + 1, cnt) - segtree2.query(1, 1, n, v[i] + 1, cnt);
      ans += (1LL * x * y);
      segtree2.update(1, 1, cnt, v[i], 1);
    }
    cout << ans << nl;
  }
  return 0;
}

// problem link: https://codeforces.com/contest/61/problem/E