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

struct CartesianTree {
    vector<int> ls, rs;
    int build(vector<int>& a) { //用stack 维护树的右链
        int n = a.size();
        ls = vector<int>(n, -1);
        rs = vector<int>(n, -1);
        vector<int> stk;
        
        for(int i = 0; i < n; i++) {
            int top = -1;
            while(stk.size() > 0 && a[stk.back()] < a[i]) { //最小堆
                top = stk.back();
                stk.pop_back();
            }
            if(stk.size() > 0){
                rs[stk.back()] = i;
            }
            if(top != -1){
                ls[i] = top;
            }
            stk.push_back(i);
        }
        
        while(stk.size() > 1) stk.pop_back();
        int root = stk.back();
        return root;
    }
} tr;

const int MOD = 1e9 + 7;
int n, m;

void dfs(vector<vector<int>>& dp, int u) {
    if(tr.ls[u] != -1) dfs(dp, tr.ls[u]);
    if(tr.rs[u] != -1) dfs(dp, tr.rs[u]);

    if(tr.ls[u] != -1 || tr.rs[u] != -1) {
        int s1 = 0, s2 = 0;
        for(int i = 1; i <= m; i++) {
            if(tr.rs[u] != -1) {
                s2 += dp[tr.rs[u]][i];
                s2 %= MOD;
            }

            if(tr.rs[u] != -1 && tr.ls[u] != -1) {
                dp[u][i] = ((s1 + 0ll) * s2) % MOD;
            } else {
                dp[u][i] = (s1 + s2);
            }

            if(tr.ls[u] != -1) {
                s1 += dp[tr.ls[u]][i];
                s1 %= MOD;
            }
        }

    } else {
        for(int i = 1; i <= m; i++) {
            dp[u][i] = 1;
        }
    }
}

void solve() {
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n, vector<int>(m + 1));
    int u = tr.build(a);
    dfs(dp, u);
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans += dp[u][i];
        ans %= MOD;
    }
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
