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
using ll = long long;

const int N = 2e5 + 100;

vector<int> g[N];
int dp[N][2];
int dfs(int u, int t) { //0 : not MEX   1 : is MEX
    if(g[u].size() == 0) {
        return 0;
    }
    if(dp[u][t] != -1) {
        return dp[u][t];
    }
    int ans = u;
    if(t == 0) {
        if(g[u].size() > 1) {
            for(int v : g[u]) {
                ans = max(ans, max(v, dfs(v, 1)));
            }
        }
    } else {
        for(int v : g[u]) {
            ans = max(ans, max(v, dfs(v, 1)));
        }
    }
    //cout << u << "   " << t << "    " << ans << endl;
    return dp[u][t] = ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n);
    int tot = 0;
    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        a[i] = vector<int>(m);
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
        tot += m;
        sort(a[i].begin(), a[i].end());
    }
    for(int i = 0; i <= tot + 10; i++) {
        g[i].clear();
        dp[i][0] = dp[i][1] = -1;
    }

    /*
    [0 : MEX1 - 1] => MEX1  [MEX1 + 1 :] => MEX1
    [MEX1] => MEX2
    */
    vector<pair<int, int>> b;
    for(int i = 0; i < n; i++) {
        set<int> s(a[i].begin(), a[i].end());
        int mex1 = -1, mex2 = -1;
        for(int j = 0; j <= a[i].size() + 10; j++) {
            if(s.find(j) == s.end()) {
                mex1 = j;
                break;
            }
        }

        for(int j = mex1 + 1; j <= a[i].size() + 10; j++) {
            if(s.find(j) == s.end()) {
                mex2 = j;
                break;
            }
        }
        g[mex1].push_back(mex2);
        //cout << mex1 << "  " << mex2 << endl;
    }

    int mx = 0;
    for(int i = 0; i <= tot + 10; i++) {
        dfs(i, 1);
        dfs(i, 0);
        mx = max(mx, dp[i][0]);
        //cout << i << "  "  << dp[i][0] << " " << dp[i][1] << endl;
    }
    
    long long ans = 0;
    int END = tot + 10;
    for(int i = 0; i <= min(END, k); i++) {
        int s = max(mx, dp[i][1]);
        s = max(s, i);
        ans += s;
    }

    if(k > END) {
        END++;
        long long s = (END + k + 0ll) * (k - END + 1) / 2;
        ans += s;
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
