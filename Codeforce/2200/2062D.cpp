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
pair<int, int> a[N];
int n;
long long add = 0;
long long dp[N];
void dfs(int pa, int u) {
    if(g[u].size() == 1 && pa != -1) {
        dp[u] = a[u].first;
        return;
    }

    long long cur = a[u].first;
    vector<long long> b;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
        b.push_back(dp[v]);
        if(dp[v] > cur) {
            cur = max(cur, min(dp[v], a[u].second + 0ll));
        }
    }

    for(long long val : b) {
        if(val > cur) {
            add += (val - cur);
        }
    }
    dp[u] = cur;
}

void solve() {
    cin >> n;
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    add = 0;
    dfs(-1, 1);
    cout << add + dp[1] << endl;
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

