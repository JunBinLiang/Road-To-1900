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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> in(n + 1);
    vector<int> dp(n + 1), best(n + 1);
    for(int u = 1; u <= n; u++) {
        int v;
        cin >> v;
        g[u].push_back(v);
        in[v]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(!in[i]) {
            q.push(i);
        }
    }

    while(q.size()) {
        int u = q.front(); q.pop();
        dp[u]++;
        for(int v : g[u]) {
            in[v]--;
            dp[v] += dp[u];
            best[v] = max(best[v], dp[u]);
            if(!in[v]) {
                q.push(v);
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        //cout << i << "  " << in[i] << "   " << dp[i] << endl;
        if(in[i] || g[i].size() == 0) { //leaf
            ans = max(ans, best[i] + 2);
        }
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
