#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 10000 + 100, M = 100000 + 10, INF = 1e8;
int n, m, S, T;
int f[M], to[M]; //流量
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, ei});
    to[ei] = v; //what each edge point to
    f[ei++] = w;
    g[v].push_back({u, ei});
    to[ei] = u;
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
            E& e = g[u][i];
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

/*
最大权独立集 (点必须非负)
独立集：选出图中的某一个点集，使得选出的所有点之间不存在边，则将这个点集称为原图的 独立集

最大权独立集 = 所有点权值 - 最小权点覆盖

讨论二分图
最小权点覆盖补集 => 最大权独立集

*/


int id(int r, int c) {
    return r * m + c;
}
vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void solve() {
    cin >> n >> m;
    int tot = 0;
    vector<vector<int>> a(n, vector<int>(m)); 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            tot += a[i][j];
        }
    }

    S = n * m, T = n * m + 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if((i + j) % 2 == 0) {
                add(g, S, id(i, j), a[i][j]);
            } else {
                add(g, id(i, j), T, a[i][j]);
            }
            if((i + j) % 2 == 0) {
                for(auto& d : dir) {
                    int r = i + d[0], c = j + d[1];
                    if(r < 0 || r >= n || c < 0 || c >= m) continue;
                    add(g, id(i, j), id(r, c), INF);
                }
            }
        }
    }
    cout << tot - dinic() << endl;
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
