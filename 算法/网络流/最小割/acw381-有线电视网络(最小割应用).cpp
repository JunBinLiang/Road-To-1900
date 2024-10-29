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
void add(vector<E> g[N], int u, int v, int w1, int w2) {
    g[u].push_back({v, ei});
    to[ei] = v; //what each edge point to
    f[ei++] = w1;
    g[v].push_back({u, ei});
    to[ei] = u;
    f[ei++] = w2;
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

bool solve() {
    /*
    枚举S, T，删除一些点后使得S T 不连通
    拆点。如果两个点在两边就等价于删掉这个点
    */
    if(scanf("%d%d",&n,&m) == EOF) return false;

    vector<pair<int, int>> edge(m);
    for(int i = 0; i < m; i++) {
        char str[20];
        scanf("%s", str);
        //提取所有的边
        int u = 0, v = 0;
        int j;
        for(j = 1; str[j] != ','; j++) u = u * 10 + str[j] - '0';
        for(j++; str[j] != ')'; j++) v = v * 10 + str[j] - '0';
        edge[i] = {u, v};
    }
    

    int ans = n;
    for(int s = 0; s < n; s++) {
        for(int t = 0; t < n; t++) {
            if(s == t) continue;
            
            ei = 0;
            for(int i = 0; i <= 2 * n + 2; i++) g[i].clear();

            //保证不会成为割边
            S = 2 * n + 1; T = 2 * n + 2;
            add(g, S, s, INF, 0);
            add(g, n + t, T, INF, 0); 
            
            for(int i = 0; i < n; i++) {
                if(i == s || i == t) {
                    add(g, i, n + i, INF, 0);
                } else {
                    add(g, i, n + i, 1, 0);
                }
            }
            for(int i = 0; i < m; i++) {
                int u = edge[i].first, v = edge[i].second;
                add(g, n + u, v, INF, 0);
                add(g, n + v, u, INF, 0);
            }
            //cout << "gg " << dinic() << endl << endl;
            ans = min(ans, dinic());
        }
    }

    cout << ans << endl;
    return true;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(solve()) {
        
    }
    return 0;
}
