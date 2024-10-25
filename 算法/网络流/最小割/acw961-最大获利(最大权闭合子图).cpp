#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 55010, M = (50000 * 3 + 5000) * 2 + 10, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
    e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (d[ver] == -1 && f[i])
            {
                d[ver] = d[t] + 1;
                cur[ver] = h[ver];
                if (ver == T) return true;
                q[ ++ tt] = ver;
            }
        }
    }
    return false;
}

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i])
    {
        cur[u] = i;
        int ver = e[i];
        if (d[ver] == d[u] + 1 && f[i])
        {
            int t = find(ver, min(f[i], limit - flow));
            if (!t) d[ver] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic()
{
    int r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

/*
最大权闭合子图
闭合图 ： 一个图的点集，并且所有边指向的点都在这个点集里面 (保证点不指向外面)
最大权闭合子图 ：求一个权值和最大的闭合子图(点的权值之和)

对应到一个割图里

构造: 
源点向任何正值的点连一条边容量是这个点的绝对值
任何负值的点向汇点连一条边容量是这个点的绝对值
其它边的容量是无限

定义简单割：所有割边都是跟源点或者汇点相连的

闭合子图里的最小割一定是个简单割(不能带无限的边)

闭合子图对应一个简单割

*/

void solve() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    S = 0, T = n + m + 1;
    for(int i = 1; i <= n; i++) {
        int w;
        scanf("%d", &w);
        add(i + m, T, w);
    }

    int tot = 0;
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        tot += c;
        add(S, i, c);
        add(i, m + a, INF);
        add(i, m + b, INF);
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


/*
https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4174
//洛谷可过
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 50000 + 5010, M = (50000 * 3 + 5000) * 2 + 10, INF = 1e8;
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
最大权闭合子图
闭合图 ： 一个图的点集，并且所有边指向的点都在这个点集里面 (保证点不指向外面)
最大权闭合子图 ：求一个权值和最大的闭合子图(点的权值之和)

对应到一个割图里

构造: 
源点向任何正值的点连一条边容量是这个点的绝对值
任何负值的点向汇点连一条边容量是这个点的绝对值
其它边的容量是无限

定义简单割：所有割边都是跟源点或者汇点相连的

闭合子图里的最小割一定是个简单割(不能带无限的边)

闭合子图对应一个简单割

*/

void solve() {
    scanf("%d%d", &n, &m);
    S = 0, T = n + m + 1;
    for(int i = 1; i <= n; i++) {
        int w;
        scanf("%d", &w);
        add(g, i + m, T, w);
    }

    int tot = 0;
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        tot += c;
        add(g, S, i, c);
        add(g, i, m + a, INF);
        add(g, i, m + b, INF);
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
*/
