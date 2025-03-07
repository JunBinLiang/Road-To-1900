//https://www.lanqiao.cn/problems/20258/learning/?contest_id=241
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;
const int SHIFT = 500000 + 1;
const int N = 1e6 + 100;
bool is[N];
int nxt[N];
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] += SHIFT;
  }

  memset(is, false, sizeof is);
  memset(nxt, -1, sizeof nxt);
  for(int i = 0; i < n; i++) {
    is[a[i]] = true;
  }

  int j = -1;
  for(int i = N - 1; i >= 0; i--) {
    if(is[i]) j = i;
    nxt[i] = j;
  }

  sort(a.begin(), a.end());
  for(int i = 1; i <= n; i++) {
    int t = a[0];
    int ans = 0;
    while(t != -1) {
      ans++;
      if(t + i >= N) break;
      t = nxt[t + i];
    }
    cout << ans << " ";
  }
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
