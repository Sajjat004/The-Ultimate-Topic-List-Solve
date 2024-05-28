#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
string building[N];
vector<vector<bool>> visited(N, vector<bool>(N, false));
int dx[8] = { 0, -1, 0, 1 };
int dy[8] = { -1, 0, 1, 0 };

bool isValid(int x, int y, int n, int m) {
  return (x >= 0 and x < n and y >= 0 and y < m and !visited[x][y] and building[x][y] == '.');
}

void dfs(int x, int y, int n, int m) {
  if (!isValid(x, y, n, m)) return;
  visited[x][y] = true;
  for (int i = 0; i < 4; ++i) dfs(dx[i] + x, dy[i] + y, n, m);
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> building[i];

  int numberOfRooms = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (isValid(i, j, n, m)) {
        dfs(i, j, n, m);
        numberOfRooms++;
      }
    }
  }
  cout << numberOfRooms << '\n';

  return 0;
}

// problem link: https://cses.fi/problemset/task/1192/