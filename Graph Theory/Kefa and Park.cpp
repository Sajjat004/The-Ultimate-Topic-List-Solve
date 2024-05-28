#include <bits/stdc++.h>
using namespace std;

const int N = (int) 1e5 + 5;
vector<bool> cats(N, 0);
vector<int> adj[N];
int catLimit;

int dfs(int u, int cat, int par = -1) {
  if (cats[u] == 1) cat++;
  else cat = 0;
  if (cat > catLimit) return 0;
  int ans = 0;
  bool child = true;
  for (int v : adj[u]) {
    if (v == par) continue;
    ans += dfs(v, cat, u);
    child = false;
  }
  if (child) ans = 1;

  return ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n >> catLimit;
  for (int i = 1; i <= n; ++i) {
    int x; cin >> x;
    cats[i] = (x == 1);
  }
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[v].push_back(u);
    adj[u].push_back(v);
  }
  cout << dfs(1, 0) << '\n';

  return 0;
}

// problem link: https://codeforces.com/problemset/problem/580/C