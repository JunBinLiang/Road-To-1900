#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;
//5:13 - 5:53
const int N = 2e5 + 10;
vector<int> g[N];
int a[N], sz[N];
long long dp[N], ans[N];
int n;

int convert(int n, int target) {
    int ans = 0;
    for(int i = 0; i < 21; i++) {
        int b1 = 0;
        if(n & (1 << i)) b1 = 1;
        if(target & (1 << i)) { //1
            ans += ((b1 ^ 1) << i);
        } else { //else
            ans += (b1 << i);
        }
    }

    if((n ^ ans) != target) {
        cout <<"gg " << n << " " << ans << " " << target << endl;
    }
    return ans;
}


void dfs1(int pa, int u) {
    sz[u] = 1;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs1(u, v);
        sz[u] += sz[v];
    }
}


void dfs2(int pa, int u) {
    if(pa != -1) {
        int c = convert(a[u], a[pa]);
        dp[u] = (c + 0ll) * sz[u];
    }
    for(int v : g[u]) {
        if(pa == v) continue;
        dfs2(u, v);
        dp[u] += dp[v];
    }
}

void dfs3(int pa, int u) {
    if(pa != -1) {
        int c = convert(a[pa], a[u]);
        long long res = ans[pa] - dp[u];
        long long c1 = dp[u] - ((c + 0ll) * sz[u]);
        int newsz = n - sz[u];
        res += ((newsz + 0ll) * c);
        ans[u] = res + c1;
        
    } else {
        ans[u] = dp[u];
    }
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs3(u, v);
    }
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        sz[i] = 0;
        ans[i] = dp[i] = 0;
    }

    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(-1, 1);
    dfs2(-1, 1);
    dfs3(-1, 1);

    for(int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }

    printf("\n");
}   

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
