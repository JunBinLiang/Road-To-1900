#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 310, M = 100000 + 10, INF = 1e8;
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

//prime : odd + even
//table must have even number of foxs
bool isp(int n) {
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

bool vis[N];
void dfs(vector<int>& a, vector<int>& path, int u) {
    vis[u] = true;
    path.push_back(u);
    for(auto& e : g[u]) {
        if(vis[e.v]) continue;
        if(a[u] % 2 == 1) {
            if(f[e.ei] == 0) {
                dfs(a, path, e.v);
            }
        } else {
            if(f[e.ei] > 0) {
                dfs(a, path, to[e.ei]);
            }
        }
    }
}

void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    S = 0; T = n + 1;
    for(int i = 1; i <= n; i++) {
        if(a[i] % 2 == 1) {
            add(g, S, i, 2);
        } else {
            add(g, i, T, 2);
        }
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] % 2 == 1) {
            for(int j = 1; j <= n; j++) {
                if(isp(a[i] + a[j])) {
                    add(g, i, j, 1);
                }
            }
        }
    }

    int flow = dinic();
    if(flow != n) {
        cout << "Impossible" << endl;
        return;
    }

    memset(vis, 0, sizeof vis);
    vector<vector<int>> ans;
    for(int i = 1; i <= n; i++) {
        if(a[i] % 2 == 1 && !vis[i]) {
            vector<int> path;
            dfs(a, path, i);
            ans.push_back(path);
        }
    }

    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) {
        auto& v = ans[i];
        cout << v.size() << " ";
        for(int u : v) cout << u << " ";
        cout << endl;
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
