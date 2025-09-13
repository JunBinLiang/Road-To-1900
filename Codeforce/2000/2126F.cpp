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

const int N = 2e5 + 100;
int a[N];
vector<pair<int, int>> g[N];
int f[N], c[N]; long long s[N];
map<int, long long> mps[N];
long long ans = 0;
void dfs(int pa, int u) {
    f[u] = pa;
    for(auto& p : g[u]) {
        int v = p.first, w = p.second;
        if(v == pa) continue;
        c[v] = w;
        s[u] += w;
        mps[u][a[v]] += w;
        if(a[u] != a[v]) ans += w;
        dfs(u, v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        mps[i].clear();
        s[i] = 0;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    ans = 0;
    dfs(-1, 1);
    
    for(int i = 0; i < m; i++) {
        int u, x;
        cin >> u >> x;
        if(a[u] == x) {
            cout << ans << endl;
            continue;
        }
        int old = a[u];
        a[u] = x;

        int p = f[u];
        if(p != -1) {
            map<int, long long>& mp = mps[p];
            long long sum = s[p];
            ans -= (sum - mp[a[p]]);
            mp[old] -= c[u];
            mp[x] += c[u];
            ans += (sum - mp[a[p]]);
        }

        map<int, long long>& mp = mps[u];
        long long sum = s[u];
        ans -= (sum - mp[old]);
        ans += (sum - mp[x]);
        cout << ans << endl;
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
