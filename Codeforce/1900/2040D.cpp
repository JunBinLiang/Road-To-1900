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
//7:24
const int N = 2e5 + 100;
vector<int> g[N];
int ans[N];
int t;

void dfs(int p, int u) {
    for(int v : g[u]) {
        if(v == p) continue;
        while(true) {
            if(t - ans[u] == 1) break;
            if(t - ans[u] > 2 && (t - ans[u]) % 2 == 0) break;
            t++;
        }
        ans[v] = t++;
        dfs(u, v);
    }
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // x + nonprime  x - nonprime
    t = 2;
    ans[1] = 1;
    dfs(-1, 1);
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
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
