#include <bits/stdc++.h>
using namespace std;
vector<int> ans;

bool dfs(long long n, long long target) {
  if (n > target) return 0;
  if (n == target) {
    ans.push_back(n);

    return 1;
  }
  bool find = dfs(n * 2, target);
  if (find) {
    ans.push_back(n);

    return 1;
  }
  find = dfs(n * 10 + 1, target);
  if (find) {
    ans.push_back(n);

    return 1;
  }

  return 0;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int a, b; cin >> a >> b;
  if (dfs(a, b)) {
    cout << "YES" << '\n';
    cout << ans.size() << '\n';
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
    cout << '\n';
  } else {
    cout << "NO" << '\n';
  }

  return 0;
}

// problem link: https://codeforces.com/contest/727/problem/A