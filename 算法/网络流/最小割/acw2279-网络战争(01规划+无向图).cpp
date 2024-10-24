#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 310, M = 1000 + 10, INF = 1e8;
int n, m, S, T;
double f[M], W[M]; //流量
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, ei});
    W[ei++] = w;
    g[v].push_back({u, ei});
    W[ei++] = w;
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

double find(int u, double limit) {
    if (u == T) return limit;
    double flow = 0;
    for (int i = cur[u]; i < g[u].size() && flow < limit; i++) {
        int v = g[u][i].v;
        cur[u] = i;  // 当前弧优化
        if (d[v] == d[u] + 1 && f[g[u][i].ei]) {
            double t = find(v, min(f[g[u][i].ei], limit - flow));
            if (t == 0) d[v] = -1;
            f[g[u][i].ei] -= t, f[g[u][i].ei ^ 1] += t, flow += t;
        }
    }
    return flow;
}


double dinic(double mid) {
    double ans = 0;
    for(int eid = 0; eid < ei; eid += 2) {
        if(W[eid] <= mid) {
            ans += (W[eid] - mid);
            f[eid] = f[eid ^ 1] = 0;
        } else {
            f[eid] = f[eid ^ 1] = W[eid] - mid;
        }
    }

    double r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r + ans;
}

void solve() {
    const double eps = 1e-8;
    cin >> n >> m >> S >> T;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(g, u, v, w);
    }

    double l = 0, r = 1e7;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (dinic(mid) < 0) r = mid;
        else l = mid;
    }
    printf("%.2lf\n", r);
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
