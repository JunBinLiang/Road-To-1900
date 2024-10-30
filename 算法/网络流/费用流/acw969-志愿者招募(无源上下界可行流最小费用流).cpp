#include <iostream>
#include <cstring>

using namespace std;

const int N = 1010, M = 24010, INF = 0x3f3f3f3f;

int n, m, S, T;
int h[N], e[M], w[M], f[M], ne[M], idx; //邻接表
int q[N], d[N], pre[N], incf[N]; //EK 算法的数组
bool st[N]; //spfa 的判重数组

void add(int a, int b, int c, int d) //添加边
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

bool spfa() //判断是否存在最短增广路
{
    int hh = 0, tt = 1;
    q[0] = S;

    memset(d, 0x3f, sizeof d);
    d[S] = 0;

    memset(incf, 0, sizeof incf);
    incf[S] = INF;

    while(hh != tt)
    {
        int t = q[hh++];
        if(hh == N) hh = 0;
        st[t] = false;

        for(int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];

            if(f[i] && d[j] > d[t] + w[i])
            {
                d[j] = d[t] + w[i];
                pre[j] = i;
                incf[j] = min(incf[t], f[i]);

                if(!st[j])
                {
                    q[tt++] = j;
                    if(tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

int EK() //EK 算法求最小费用最大流
{
    int cost = 0;
    while(spfa())
    {
        int t = incf[T];
        cost += t * d[T];

        for(int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
    return cost;
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h); //初始化邻接表

    S = 0, T = n + 2; //源点、汇点
    //由于每个点只有一条入边一条出边，入边下界就是前一天的人数，出边下界就是当天的人数
    int last = 0; //记录前一天的人数（入边下界）
    for(int i = 1; i <= n; i++)
    {
        int cur; //记录当天的人数（出边下界）
        scanf("%d", &cur);

        if(last > cur) add(S, i, last - cur, 0); //C入 > C出
        else if(last < cur) add(i, T, cur - last, 0); //C出 > C入

        add(i, i + 1, INF - cur, 0); //从每个点向下一个点连边（即该点的出边），容量为 INF - cur（下界），费用是 0

        last = cur; //更新前一天的人数
    }
    add(S, n + 1, last, 0); //点 n + 1 一定是入边是第 n 天的人数，出边是 0

    while(m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        add(b + 1, a, INF, c); //从 b + 1 向 a 连边，容量是 INF，费用是该志愿者的费用
    }

    printf("%d\n", EK());

    return 0;
}
