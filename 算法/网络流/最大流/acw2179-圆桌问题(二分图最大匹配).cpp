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

const int N = 1e5 + 10, M = 2e5 + 10;
long long INF = 1e16;
int n, m, S, T;
long long f[M]; //流量
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

long long find(int u, long long limit) {
    if (u == T) return limit;
    long long flow = 0;
    for (int i = cur[u]; i < g[u].size() && flow < limit; i++) {
        int v = g[u][i].v;
        cur[u] = i;  // 当前弧优化
        if (d[v] == d[u] + 1 && f[g[u][i].ei]) {
            long long t = find(v, min(f[g[u][i].ei], limit - flow));
            if (!t) d[v] = -1;
            f[g[u][i].ei] -= t, f[g[u][i].ei ^ 1] += t, flow += t;
        }
    }
    return flow;
}

long long dinic() {
    long long r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    cin >> n >> m;
    int sum = 0;
    S = 0;
    T = n + m + 1;

    for(int i = 1; i <= n; i++) { //people
        int r;
        cin >> r;
        add(g, S, i, r);
        sum += r;
        for(int table = n + 1; table <= n + m; table++) {
            add(g, i, table, 1);
        }
    }

    for(int i = 1; i <= m; i++) {
        int cap;
        cin >> cap;
        add(g, n + i, T, cap);
    }

    int flow = dinic();
    if(flow != sum) cout << 0 << endl;
    else {
        cout << 1 << endl;
        for(int u = 1; u <= n; u++) {
            for(auto& e : g[u]) {
                if(e.v != S && f[e.ei] == 0) {
                    cout << e.v - n << " ";
                }
            }
            cout << endl;
        }
    }
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
