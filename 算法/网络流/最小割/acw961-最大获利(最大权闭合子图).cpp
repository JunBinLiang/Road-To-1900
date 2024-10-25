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
