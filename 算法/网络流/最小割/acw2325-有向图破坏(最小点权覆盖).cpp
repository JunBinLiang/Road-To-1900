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

/*
最小权点覆盖

点覆盖集: 给一个无向图，选一些点，使得每条边都至少有一个点在这个集合里 (NP问题)
最小权点覆盖 ：非负点权，找一个总权值最小的 


处理二分图

二分图:
(每个点的权值是1的时候)最大匹配数 = 最小点覆盖数 = n - 最大独立集数 (权值非1的时候，得用网络流解决)


建立图：
内部边容量 INF
S -> group1点 容量 = 点权值
group2点 -> T 容量 = 点权值

*/

int vis[N];
void dfs(int u) { //搜S集合
    vis[u] = 1;
    for(int i = 0; i < g[u].size(); i++) {
        E& e = g[u][i];
        if(f[e.ei] && vis[e.v] == -1) {
            dfs(e.v);
        }
    }
}

void solve() {
    cin >> n >> m;
    S = 0;
    T = 2 * n + 1;
    for(int i = 1; i <= n; i++) {  //删除点i 射入 边的代价 +
        int w; cin >> w;
        add(g, S, i, w);
    }

    for(int i = 1; i <= n; i++) { //删除点i 射出 边的代价 -
        int w; cin >> w;
        add(g, n + i, T, w);
    }

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(g, v, n + u, INF);
    }

    cout << dinic() << endl;
    //输出方案： 简单割变成点覆盖集
    //1. 怎么用最大流 求出最小割  (跑完最大流后的残留网络中，往容量的于0的走，能走到的点放S，其余放T。在原网络里找所有的正向边可以从S 到T的边，不包含反向边)
    //2. 最小割求点覆盖集

    memset(vis, -1, sizeof vis);
    dfs(S);

    for(int i = 0; i <= 2 * n + 1; i++) {
        if(vis[i] == -1) {
            vis[i] = 2;
        }
    }

    //枚举正向边
    vector<string> ans;
    for(int eid = 0; eid < ei; eid += 2) {
        int v = to[eid], u = to[eid ^ 1];
        if(vis[u] == 1 && vis[v] == 2) { //S -> T, 割边 u -> v
            if(u == S) {
                ans.push_back(to_string(v) + " +");
            } else if(v == T) {
                ans.push_back(to_string(u - n) + " -");
            }
        }
    }

    cout << ans.size() << endl;
    for(string& s : ans) cout << s << endl;
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
