#include <bits/stdc++.h>
using namespace std;

template <typename type> class FenwickTree {
private:
  vector<type> tree;
  int n;

public:

  FenwickTree(int n) {
    this->n = n;
    tree.assign(n + 2, 0);
  }

  void update(int idx, type val) {
    for ( ; idx <= n; idx += (idx & -idx)) tree[idx] += val;
  }

  type query(int idx) {
    type sum = 0;
    for ( ; idx > 0; idx -= (idx & -idx)) sum += tree[idx];

    return sum;
  }

  void update(int l, int r, int val) {
    update(l, val);
    update(r + 1, -val);
  }

  type query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, q; cin >> n >> q;
  vector<int> nums(n);
  for (int& x : nums) cin >> x;
  vector<vector<pair<int, int>>> queries(n + 1);
  for (int i = 0; i < q; ++i) {
    int a, b; cin >> a >> b;
    queries[a].push_back({b, i});
  }
  
  FenwickTree<int> fenwickTree(n);
  vector<int> ans(q);
  map<int, int> lastIndex;
  for (int i = n - 1; i >= 0; --i) {
    if (lastIndex.count(nums[i]) > 0) {
      fenwickTree.update(lastIndex[nums[i]] + 1, -1);
    }
    lastIndex[nums[i]] = i;
    fenwickTree.update(i + 1, 1);
    for (auto [b, j] : queries[i + 1]) {
      ans[j] = fenwickTree.query(b);
    }
  }

  for (int i = 0; i < q; ++i) cout << ans[i] << " \n"[i == q - 1];

  return 0;
}
