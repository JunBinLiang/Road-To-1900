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

using namespace std;
const int N = 2e5 + 100;
vector<int> g[N];
int dp[N][3];
int ans = 0;
void dfs(int pa, int u) {
    if(pa != -1 && g[u].size() == 1) { //leaf
        dp[u][0] = 1; 
        dp[u][1] = 0;
        dp[u][2] = 0;
        return;
    }

    dp[u][0] = 1; 
    vector<int> a;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
        a.push_back(dp[v][1]);
        dp[u][2] = max(dp[u][2], dp[v][2]);
        ans = max(ans, dp[v][2] + 1);
        ans = max(ans, dp[v][1] + 1);
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int sz = a.size();
    
    dp[u][1] = a.size();
    dp[u][1] = max(dp[u][1], a[0] + sz - 1);
    
    if(a.size() == 1) {
        dp[u][2] = max(dp[u][2], a[0]);
    } else if(a.size() >= 2) {
        dp[u][2] = max(dp[u][2], a[0] + a[1] + sz - 2);
    } 
    dp[u][2] = max(dp[u][2], dp[u][1]);
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = 0;
    }
    
    ans = 0;
    dfs(-1, 1);
    ans = max(ans, dp[1][0]);
    ans = max(ans, dp[1][1]);
    ans = max(ans, dp[1][2]);
    cout << ans << endl;
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
