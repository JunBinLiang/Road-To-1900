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

const int N = 3e5 + 100;
vector<int> g[N];
int d[N], sz[N];
long long t1 = 0, t2 = 0, t3 = 0;
int n;
/*
d[u] + d[v] - 2 * d[lca] - |d[u] - d[v]| - 1

lca(u, v) != u and lca(u, v) != v
*/

void dfs(int pa, int u, int h) {
    d[u] = h;
    sz[u] = 1;
    long long pairs = 0;
    long long s = 0;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v, h + 1);
        sz[u] += sz[v];
        pairs += (s * sz[v]);
        s += sz[v];
    }
    
    t1 -= (2ll * d[u] * pairs);
    t1 -= pairs;
    t2 += ((d[u] + 0ll) * (n - sz[u] - d[u]));
    
}

void solve() {
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

    t1 = 0;
    t2 = 0;
    t3 = 0;
    dfs(-1, 1, 0);
    
    //cout << "gg " << ans <<"  " << t << endl;
    
    sort(d + 1, d + n + 1);
    long long s = 0;
    for(int i = 1; i <= n; i++) {
        s += d[i];
        long long x = ((d[i] + 0ll) * i);
        x -= s;
        t3 += x;
        t3 += ((0ll + d[i]) * (d[i] + 1) / 2);
        t3 -= ((d[i] + 0ll) * (d[i] + 1));
    } 
    cout << (t1 + t2 - t3) << endl;
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

