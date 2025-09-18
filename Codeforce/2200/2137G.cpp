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

const int N = 2e5 + 10;
vector<int> g[N], rev[N];
int dp[N][2];
int sums[N][2];
bool vis[N];

void sub(int u, int x, int y) {
    sums[u][0] -= x;
    sums[u][1] -= y;
}

void add(int u, int x, int y) {
    sums[u][0] += x;
    sums[u][1] += y;
}

void dfs(int u, int o0, int o1) {
    //cout << "update  " << u << "  " << dp[u][0] << " " << dp[u][1] <<"     | " << sums[u][0] << " " << sums[u][1] << endl;
    for(int v : rev[u]) {
        if(vis[v]) continue;
        int old0 = dp[v][0], old1 = dp[v][1];
        sub(v, o0, o1);
        add(v, dp[u][0], dp[u][1]);

        //0 -> 1
        if(sums[v][1] != g[v].size()) {
            dp[v][0] = 1;
        } else {
            dp[v][0] = 0;
        }

        //1 -> 0
        if(sums[v][0] != g[v].size()) {
            dp[v][1] = 1;
        } else {
            dp[v][1] = 0;
        }

        
//cout << "old " << v << " " << old0 << " " << old1 << "    |" << dp[v][0] << " " << dp[v][1] << endl;
        if(old0 != dp[v][0] || old1 != dp[v][1]) {
            dfs(v, old0, old1);
        }
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        rev[i].clear();
        dp[i][0] = dp[i][1] = -1;
        sums[i][0] = sums[i][1] = 0;
        vis[i] = false;
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rev[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        dp[i][0] = 1; // A can win
        dp[i][1] = 0; // B always lost
    }
    for(int i = 1; i <= n; i++) {
        sums[i][0] = g[i].size();
        sums[i][1] = 0;
    }

    //A : reach to leave node in order to win (can not go to red)
    //B : reach any red node
    for(int i = 0; i < q; i++) {
        int op, u;
        cin >> op >> u;
        if(op == 1) {
            int o0 = dp[u][0];
            int o1 = dp[u][1];
            dp[u][0] = 0;
            dp[u][1] = 1;
            vis[u] = true;
            dfs(u, o0, o1);
            //cout <<  endl << endl;
        } else {
            if(dp[u][0] == 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
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
