#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;
vector<int> adj[N];
vector<int> subTreeSum(N, 0);

void dfs(int u) {
  subTreeSum[u] = 1;
  for (int v : adj[u]) {
    dfs(v);
    subTreeSum[u] += subTreeSum[v];
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  for (int i = 2; i <= n; ++i) {
    int par; cin >> par;
    adj[par].push_back(i);
  }
  dfs(1);
  for (int i = 1; i <= n; ++i) cout << subTreeSum[i] - 1 << " \n"[i == n];
  return 0;
}

// problem link: https://cses.fi/problemset/task/1674/