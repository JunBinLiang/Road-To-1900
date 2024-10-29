#include <string>
#include <sstream>
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

void dfs(vector<int>& vis, int u) {
    vis[u] = 1;
    for(int i = 0; i < g[u].size(); i++) {
        E& e = g[u][i];
        if(!vis[e.v] && f[e.ei] > 0) {
            dfs(vis, e.v);
        }
    }
}

void solve() {
    string line;
    getline(cin, line);
    stringstream sin(line);
    sin >> m >> n;

    int tot = 0;
    S = 0; T = n + m + 1;

    for(int i = 1; i <= m; i++) { //实验
        getline(cin, line);
        stringstream sin(line);
        int w;
        sin >> w;
        tot += w;
        add(g, S, i, w);

        int u;
        while(sin >> u){
            add(g, i, m + u, INF);
        }
    }   


    for(int i = 1; i <= n; i++) { //仪器费用
        int w;
        cin >> w;
        add(g, m + i, T, w);
    }

    int flow = dinic();

    vector<int> vis(m + n + 2);
    dfs(vis, S);
    for(int i = 1; i <= m; i++) {
        if(vis[i] == 1) {
            cout << i << " "; 
        }
    }
    cout << endl;
    for(int i = m + 1; i <= m + n; i++) {
        if(vis[i] == 1) {
            cout << i - m << " "; 
        }
    }
    cout << endl;
    cout << tot - flow << endl;
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
