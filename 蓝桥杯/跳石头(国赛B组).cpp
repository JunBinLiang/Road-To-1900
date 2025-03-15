//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P10914
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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 40005;
bitset<N> dp[N];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> g(n + 1);
    
    for(int i = 1; i <= n; i++) {
        if(i + a[i] <= n) {
            g[i].push_back(i + a[i]);
        }
        if(i + i <= n) {
            g[i].push_back(i + i);
        }
    }
   
   int ans = 0;
    for(int i = n; i >= 1; i--) {
        dp[i][a[i]] = 1;
        for(int p : g[i]) {
            dp[i] |= dp[p];
        }
        ans = max(ans, (int)(dp[i].count()));
    }
    cout << ans << endl;
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
