//https://www.lanqiao.cn/problems/21070/learning/?contest_id=263
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <deque>
using namespace std;
const int N = 510;
int a[510][510];
int c[N];
int n;
vector<int> g[N];
bool good = false;
void dfs(int u, int col) {
  if(!good) return;
  c[u] = col;
  //cout << "dfs " << u << " " << col << endl;
  for(int v : g[u]) {
    if(c[v] != -1) {
      if(c[v] == c[u]) good = false;
    } else {
      dfs(v, col ^ 1);
    }
  }
}

bool ok(int mid) {
  good = true;
  for(int i = 0; i <= n; i++) g[i].clear();
  for(int i = 0; i <= n; i++) c[i] = -1;
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if(a[i][j] < mid) { //can not in the same group
        g[i].push_back(j);
        g[j].push_back(i);
      }
    }
  }
  for(int i = 0; i < n; i++) {
    if(c[i] == -1) {
      dfs(i, 0);
    }
  }
  return good;
}
int main()
{
  // 请在此输入您的代码
  cin >> n;
  int r = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> a[i][j];
      r = max(r, a[i][j]);
    }
  }
  int l = 0;
  int ans = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    //cout << mid << endl;
    if(ok(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans << endl;
  return 0;
}
