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

const int N = 2e5 + 10, M = 4e5 + 10;
long long INF = 1e16;
int n, m, S, T;
long long f[M]; //流量
long long A[N], L[N];
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int lo, int hi) {
    g[u].push_back({v, ei});
    L[ei] = lo;
    f[ei++] = hi - lo;
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
    int s, t;
    cin >> n >> m >> s >> t;
    S = 0; T = n + 1;
    while(m--) {
        int u, v, c1, c2;
        cin >> u >> v >> c1 >> c2;
        add(g, u, v, c1, c2);
        A[u] -= c1, A[v] += c1;
    }

    int tot = 0;
    for (int i = 1; i <= n; i ++ )
        if (A[i] > 0) add(g, S, i, 0, A[i]), tot += A[i];
        else if (A[i] < 0) add(g, i, T, 0, -A[i]);

    add(g, t, s, 0, INF);
    if (dinic() < tot) cout << "No Solution" << endl;
    else {
        int ans = f[ei - 1];
        S = t, T = s;
        f[ei - 1] = f[ei - 2] = 0;
        cout << ans - dinic() << endl;
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
}a
