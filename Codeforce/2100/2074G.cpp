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

const int N = 500;
int a[N];
long long dp[N][N];
long long dfs(int l, int r) {
    if(r - l + 1 < 3) {
        return 0;
    }
    if(dp[l][r] != -1) {
        return dp[l][r];
    }
    long long ans = 0;
    for(int i = l; i < r; i++) {
        ans = max(ans, dfs(l, i) + dfs(i + 1, r));
    }

    for(int i = l + 1; i < r; i++) {
        ans = max(ans, dfs(l + 1, i - 1) + dfs(i + 1, r - 1) + a[l] * a[r] * a[i]);
    }

    return dp[l][r] = ans;
}

void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }

    long long ans = dfs(1, n);
    cout << ans << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
