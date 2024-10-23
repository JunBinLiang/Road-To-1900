#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 310, M = 100000 + 10, INF = 1e8;
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


int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

bool check(pair<int, int>& a, pair<int, int>& b, double D) {
    const double eps = 1e-8;
    double dx = a.first - b.first, dy = a.second - b.second;
    return dx * dx + dy * dy < D * D + eps;
}

pair<int, int> p[N];
void solve() {
    double D;
    cin >> n >> D;
    ei = 0;
    S = 0;
    for(int i = 0; i <= 2 * n; i++) g[i].clear();
    
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        p[i] = {x, y};
        tot += a;
        add(g, S, i, a);
        add(g, i, i + n, b);
    } 

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(check(p[i], p[j], D)) {
                add(g, n + i, j, INF);
                add(g, n + j, i, INF);
            }   
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        T = i;
        //对图clean，可以用正向边加反向边的容量
        for(int eid = 0; eid < ei; eid += 2) {
            f[eid] += f[eid ^ 1];
            f[eid ^ 1] = 0;
        }
        if(dinic() == tot) {
            ans++;
            cout << i - 1 << " ";
        }
    }

    if(ans == 0) cout << -1 << endl;
    else cout << endl;
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
