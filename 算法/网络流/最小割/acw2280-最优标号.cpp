#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 610, M = 100000 + 10, INF = 1e8;
int n, m, S, T;
int f[M]; //流量
int d[N], cur[N]; //分层图

pair<int, int> edges[M];
int A[N];

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) { //无向图
    g[u].push_back({v, ei});
    f[ei++] = w;
    g[v].push_back({u, ei});
    f[ei++] = w;
}

bool bfs() {
    memset(d, -1, sizeof d);
    queue<int> q;
    q.push(S);
    d[S] = 0;
    cur[S] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0; i < g[u].size(); i++) {
            E e = g[u][i];
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


int dinic(int ith) {
    //clear the graph
    for(int i = 0; i < N; i++) {
        g[i].clear();
    }
    ei = 0;

    for(int i = 0; i < m; i++) {
        add(g, edges[i].first, edges[i].second, 1);
    }
    for(int i = 1; i <= n; i++) {
        if(A[i] == -1) continue;
        if(A[i] & (1 << ith)) {//强制归入S 的集合
            add(g, S, i, INF);
        } else { //强制归入T 的集合
            add(g, i, T, INF);
        }
    }

    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    cin >> n >> m;
    S = 0; T = n + 1;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    memset(A, -1, sizeof A);
    int k;
    cin >> k;
    for(int i = 0; i < k; i++) {
        int u, val;
        cin >> u >> val;
        A[u] = val;
    }

    long long ans = 0;
    for(int i = 0; i <= 30; i++) {
        int cnt = dinic(i);
        ans += (((1 << i) + 0ll) * cnt); 
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
