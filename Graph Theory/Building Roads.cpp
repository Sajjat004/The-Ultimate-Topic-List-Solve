#include <bits/stdc++.h>
using namespace std;

const int N = (int) 1e5 + 5;
vector<int> adj[N];
vector<bool> visited(N, 0);

void dfs(int u) {
  visited[u] = true;
  for (int v : adj[u]) {
    if (!visited[v]) dfs(v);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;

  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> component;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      dfs(i);
      component.push_back(i);
    }
  }

  cout << component.size() - 1 << '\n';
  for (int i = 1; i < component.size(); ++i) {
    cout << component[i - 1] << " " << component[i] << '\n';
  }
  return 0;
}

// problem link: https://cses.fi/problemset/task/1666/