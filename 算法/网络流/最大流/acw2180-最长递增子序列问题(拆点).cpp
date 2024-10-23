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

const int N = 1e4 + 10, M = 200000 + 10, INF = 1e8;
int n, m, S, T;
int f[M]; //流量
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, ei});
    f[ei++] = w;
    g[v].push_back({u, ei});
    f[ei++] = 0;
}

bool bfs() {
    memset(d, -1, sizeof d);
    queue<int> q;
    q.push(S);
    d[S] = 0;
    cur[S] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto& e : g[u]) {
            if(d[e.v] == -1 && f[e.ei]) {
                d[e.v] = d[u] + 1;
                cur[e.v] = 0; 
                q.push(e.v);
                if(e.v == T) return true;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; i < g[u].size() && flow < limit; i++) {
        int v = g[u][i].v;
        cur[u] = i;  // 当前弧优化
        if (d[v] == d[u] + 1 && f[g[u][i].ei]) {
            int t = find(v, min(f[g[u][i].ei], limit - flow));
            if (!t) d[v] = -1;
            f[g[u][i].ei] -= t, f[g[u][i].ei ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    cin >> n;
    vector<int> a(n + 1);
    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    S = 0;
    T = 2 * n + 1;

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] = 1;
        add(g, i, i + n, 1);
        for(int j = i - 1; j >= 1; j--) {
            if(a[j] <= a[i]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        for(int j = i - 1; j >= 1; j--) {
            if(dp[j] + 1 == dp[i] && a[j] <= a[i]) {
                add(g, n + j, i, 1);
            }
        }
        if(dp[i] == 1) {
            add(g, S, i, 1);
        }
        ans = max(ans, dp[i]);
    }

    for(int i = 1; i <= n; i++) {
        if(dp[i] == ans) {
            add(g, i + n, T, 1);
        }
    }


    cout << ans << endl;
    if(ans == 1) {
        cout << n << endl;
        cout << n << endl;
        return;
    }

    int flow = dinic();
    cout << flow << endl;
    //if a[1] and a[n] can use multiple times
    //把已有的路劲(可以加的路劲) capcity 变大
    for(int u = 0; u <= 2 * n + 1; u++) {
        for(auto& e : g[u]) {
            int v = e.v;
            if(u == S && (v == 1 || v == n)) f[e.ei] = INF;
            else if(u == 1 && v == 1 + n) f[e.ei] = INF;
            else if(u == n && v == n + n) f[e.ei] = INF;
            else if(u == n + n && v == T) f[e.ei] = INF;
        }
    }
    cout << flow + dinic() << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
