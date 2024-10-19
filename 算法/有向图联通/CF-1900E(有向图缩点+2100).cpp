#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 2e5 + 10;
struct E {
    int v, w, ei;
};
vector<E> g[N];
int a[N];
int n, m, ei = 0;

void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, w, ei++});
    g[v].push_back({u, w, ei++});
}

void add1(vector<E> g[N], int u, int v, int w) { //1 direction
    g[u].push_back({v, w, ei++});
}

int t = 0, top = 0, scc_cnt = 0;
int dfn[N], low[N];
bool in_stk[N];
int stk[N], id[N], sz[N];
long long sums[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++ t;
    stk[ ++ top] = u, in_stk[u] = true;

    for(auto& e : g[u]) {
        int v = e.v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt] ++ ;
            sums[scc_cnt] += a[y];
        } while (y != u);
    }
}

void solve() {
    cin >> n >> m;
    //cout << n << "  " << m << endl;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ei = 0; t = 0; top = 0; scc_cnt = 0;
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 0; i <= n; i++) {
        dfn[i] = low[i] = 0;
        in_stk[i] = false;
        sz[i] = 0;
        sums[i] = 0;
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add1(g, u, v, 0);
    }

    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    
    //Topological graph
    vector<int> in(n + 1);
    vector<vector<int>> graph(n + 1);
    vector<int> d(n + 1);
    vector<long long> dp(n + 1, -1);
    queue<int> q;
    for(int u = 1; u <= n; u++) {
        for(auto& e : g[u]) {
            int v = e.v;
            if(id[u] != id[v]) {
                graph[id[u]].push_back(id[v]);
                in[id[v]]++;
            }
        }
    }

    for(int i = 1; i <= scc_cnt; i++) {
        if(in[i] == 0) {
            q.push(i);
            d[i] = sz[i];
            dp[i] = sums[i];
        }
    }

    while(q.size() > 0) {
        int u = q.front();
        q.pop();
        for(int v : graph[u]) {
            if(d[u] + sz[v] >= d[v]) {
                if(d[u] + sz[v] == d[v]) {
                    dp[v] = min(dp[v], dp[u] + sums[v]);
                } else {
                    d[v] = d[u] + sz[v];
                    dp[v] = dp[u] + sums[v];
                }
            }
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }

    int ans1 = 0; long long ans2 = 0;
    for(int i = 1; i <= scc_cnt; i++) {
        if(d[i] >= ans1) {
            if(d[i] == ans1) {
                ans2 = min(ans2, dp[i]);
            } else {
                ans1 = d[i];
                ans2 = dp[i];
            }
        }
    }
    cout << ans1 << " " << ans2 << endl;
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
