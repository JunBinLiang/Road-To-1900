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
const int N = 2e5 + 10;
vector<int> g[N];
map<int, int> mp;
int deg[N];
int ans = 0;

void add(int k) {
    mp[k]++;
}

void del(int k) {
    mp[k]--;
    if(mp[k] == 0) mp.erase(k);
}

void dfs(int pa, int u) {
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
    }

    int cnt = deg[u];
    for(int v : g[u]) { //nxt
        del(deg[v]);
        add(deg[v] - 1);
    }
    del(deg[u]);

    
    auto it = mp.end();
    it--;
    
    //cout << u << "  " << cnt << endl;
    //cout << "gg " << it -> first << endl << endl;

    if(cnt == 1) {
        if(it -> first > 1) {
            ans = max(ans, it -> first);
        }
    } else {
        if(it -> first == 0) {
            cnt--;
            ans = max(ans, cnt);
        } else {
            ans = max(ans, cnt + it -> first - 1);
        }
    }
    
    for(int v : g[u]) { //nxt
        del(deg[v] - 1);
        add(deg[v]);
    }
    add(deg[u]);
}

void solve() {
    int n, m;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        deg[i] = 0;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    if(n == 2) {
        cout << 0 << endl;
        return;
    }

    mp.clear();
    for(int i = 1; i <= n; i++) {
        mp[deg[i]]++;
    }

    ans = 0;
    dfs(-1, 1);
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

