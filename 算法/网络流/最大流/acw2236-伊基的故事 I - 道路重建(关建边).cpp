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

const int N = 1000 + 10, M = 10000 + 10, INF = 1e8;
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

void bfs1(vector<bool>& vis, int s) {
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto& e : g[u]) {
            if(f[e.ei] && !vis[e.v]) {
                vis[e.v] = true;
                q.push(e.v);
            }
        }
    }
}

void bfs2(vector<bool>& vis, int s) {
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto& e : g[u]) {
            if(f[e.ei ^ 1] && !vis[e.v]) {
                vis[e.v] = true;
                q.push(e.v);
            }
        }
    }
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

/*
题意: 把一条边容量增加，他能使总流量增加。有多少条这样的边
*/
void solve() {
    cin >> n >> m;
    S = 0; T = n - 1;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(g, u, v, w);
    }

    /*
    1. 如果流量是未满，无必要增加
    2. 对于满流量的边增大的话，他得有增广路才能使最终容量增大
    */

    dinic();
    vector<bool> vis1(n), vis2(n);
    bfs1(vis1, S);
    bfs2(vis2, T); //反着走需要注意

    int ans = 0;
    for(int u = 0; u < n; u++) {
        for(auto& e : g[u]) {
            if(e.ei % 2 == 1) continue; //反向边
            if(f[e.ei] != 0) continue; //流量未满
            if(vis1[u] && vis2[e.v]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
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
