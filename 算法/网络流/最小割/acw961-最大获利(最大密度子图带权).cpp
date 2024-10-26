#include <iostream>
#include <cstring>

using namespace std;

const int N = 5010, M = 60000 * 2 + 10, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx; //邻接表
int q[N], d[N], cur[N]; //队列、层数、当前弧
int deg[N]; //记录从每个点出发的边的权值之和
int p[N]; //记录每个点的权值

void add(int a, int b, int c, int d) //添加边
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = d, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() //建立分层图，判断是否存在增广路径
{
    int hh = 0, tt = 0;
    q[0] = S;

    memset(d, 0, sizeof d);
    d[S] = 1;

    cur[S] = h[S];

    while(hh <= tt)
    {
        int t = q[hh++];

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];

            if(!d[j] && w[i])
            {
                d[j] = d[t] + 1;
                cur[j] = h[j];

                if(j == T) return true;

                q[++tt] = j;
            }
        }
    }
    return false;
}

int find(int u, int flow) //统计从 u 往终点能传输的最大流量，上限是 flow
{
    if(u == T) return flow;

    int rest = flow;
    for(int i = cur[u]; i != -1 && rest; i = ne[i])
    {
        cur[u] = i;

        int j = e[i];
        if(d[j] == d[u] + 1 && w[i])
        {
            int k = find(j, min(w[i], rest));
            if(!k) d[j] = 0;

            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int dinic() //求最小割
{
    int maxf = 0, flow;
    while(bfs())
        while(flow = find(S, INF)) maxf += flow;
    return maxf;
}

int main()
{
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++) scanf("%d", &p[i]), p[i] *= -1; //点权是要减去的，是负的

    memset(h, -1, sizeof h); //初始化邻接表

    S = 0, T = n + 1; //源点、汇点
    while(m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        deg[a] += c, deg[b] += c; //记录从每个点出发的边的权值之和
        add(a, b, c, c); //无向边（四条边合并成两条边）
    }

    //保证 U + 2 * g - 2 * p[i] - deg[i] >= 0，本题 g = 0，U >= 2 * p[i] + deg[i]
    int U = 0;
    for(int i = 1; i <= n; i++) U = max(U, 2 * p[i] + deg[i]);

    for(int i = 1; i <= n; i++)
    {
        add(S, i, U, 0); //从源点向每个点连一条容量是 U 的边
        add(i, T, U - 2 * p[i] - deg[i], 0); //从每个点向汇点连一条容量是 U - 2 * g - 2 * p[i] - deg[i] 的边
    }

    printf("%d\n", (U * n - dinic()) / 2);

    return 0;
}
