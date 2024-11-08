#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  

const int N = 2010;
vector<int> g[N];
int a[N];
long long dp[N];
int n, root;
void dfs(int pa, int u, long long mid) {
    long long s = 0;
    for(int& v : g[u]) {
        if(v == pa) continue;
        dfs(u, v, mid);
        s += dp[v];
    }
    
    long long round = mid / n;
    if((mid % n) >= u) round++;

    if(round >= a[u]) {
        long long remain = round - a[u];
        if(remain >= s) {
            dp[u] = (remain - s) % 2;
        } else {
            dp[u] = (s - remain);
        }
    } else {
        dp[u] = (a[u] - round) + s;
    }
    //cout << round << "    " << u << "  " << dp[u] << endl;
}

bool ok(long long mid) {
    dfs(-1, root, mid);
    return dp[root] == 0;
}

void solve() {
    cin >> n >> root;
    for(int i = 0; i <= n; i++) g[i].clear();
    long long s = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s += a[i];
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v; 
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    
    long long ans = 10000000000000ll;
    for(int i = 1; i <= n; i++) {
        long long shift = 2e9;
        bool check = ok(shift * 2 * n + i);
        if(!check) continue;
        long long l = 0, r = 2e9;
        while(l <= r) {
            long long mid = l + (r - l) / 2;
            long long mmid = mid * 2 * n + i;
            if(ok(mmid)) {
                ans = min(ans, mmid);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

    }

    for(int i = 1; i <= n; i++) {
        long long shift = 2e9;
        bool check = ok(shift * 2 * n + i + n);
        if(!check) continue;
        long long l = 0, r = 2e9;
        while(l <= r) {
            long long mid = l + (r - l) / 2;
            long long mmid = mid * 2 * n + i + n;
            if(ok(mmid)) {
                ans = min(ans, mmid);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    
    if(ok(0)) {
        ans = 0;
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
