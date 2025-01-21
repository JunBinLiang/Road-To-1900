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

const int MOD = 998244353;

/*
Assume we have the following tree : 1 - 2 - 3 - 4
f(1) = 1
f(4) = 0
f(2) = 1 / 2 * f(1) + 1 / 2 * f(3) = 1 / 2 + 1 / 2 * f(3)
f(3) = 1 / 2 * f(4) + 1 / 2 * f(2) = 1 / 2 * f(2)
f(2) = 1 / 2 + 1 / 4 f(2)
*/

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        // q is quotient
        long long q = a / m;
        long long t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

const int N = 2e5 + 10;
vector<int> g[N];
int h[N];
long long dp[N];
void dfs1(int pa, int u) {
    if(pa != -1 && g[u].size() == 1) { //leaf
        h[u] = 0;
        return;
    }
    int minh = 1e9;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs1(u, v);
        minh = min(minh, h[v]);
    }
    h[u] = minh + 1;
}

void dfs2(int pa, int u) {
    if(pa != -1 && g[u].size() == 1) { //leaf
        dp[u] = 0;
        return;
    }

    if(u == 1) {
        dp[u] = 1;
    } else {
        if(pa == 1) {
            dp[u] = (h[u]) * modInverse(h[u] + 1, MOD);
            dp[u] %= MOD;
        } else {
            long long w = dp[pa] * modInverse(h[u] + 1, MOD);
            w %= MOD;
            w *= h[u];
            w %= MOD;
            dp[u] = w;
        }
    }

    for(int v : g[u]) {
        if(v == pa) continue;
        dfs2(u, v);
    }
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
    
    dfs1(-1, 1);
    dfs2(-1, 1);
    for(int i = 1; i <= n; i++) cout << dp[i] << " ";
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
