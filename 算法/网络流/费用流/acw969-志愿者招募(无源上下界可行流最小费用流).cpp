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


/*
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int N = 5050, M = 2e5 + 100;
long long INF = 1e12;
int n, m, S, T;
long long f[M], weight[M]; 
int to[M]; //流量
long long d[N], incf[N]; //分层图
int pre[N];
bool st[N];

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0; int e = 0;
void add(vector<E> g[N], int u, int v, long long cap, long long w) {
    g[u].push_back({v, ei});
    to[ei] = v;
    weight[ei] = w;
    f[ei++] = cap;
    
    g[v].push_back({u, ei});
    to[ei] = u;
    weight[ei] = -w;
    f[ei++] = 0;
}

bool spfaMin() {//判断是否存在最短增广路
    for(int i = 0; i <= 2 * n + 1; i++) { //Number of nodes
        d[i] = INF;
        st[i] = false;
        incf[i] = 0;
        pre[i] = -1;
    }
    queue<int> q;
    q.push(S);
    d[S] = 0;
    incf[S] = INF;
    while(q.size()) {
        int u = q.front(); q.pop();
        st[u] = false;
        for(int i = 0; i < g[u].size(); i++) {
            E& e = g[u][i];
            if(f[e.ei] && d[e.v] > d[u] + weight[e.ei]) {
                d[e.v] = d[u] + weight[e.ei];
                pre[e.v] = e.ei;
                incf[e.v] = min(incf[u], f[e.ei]);
                if(!st[e.v]) {
                    q.push(e.v);
                    st[e.v] = true;
                }
            }
        }
    }
    return incf[T] > 0;
}

void EKMin(long long& flow, long long& cost) {
    while(spfaMin()) //如果存在最短增广路
    {   
        long long t = incf[T]; //记录当前最短增广路的最大流量
        flow += t, cost += t * d[T]; //累加最大流和最小费用
        //增广路流变化
        int u = T;
        while(u != S) {
            int eid = pre[u];
            f[eid] -= t;
            f[eid ^ 1] += t;
            u = to[eid ^ 1];
        }
    }
}


void solve() {
    cin >> n >> m;
    S = 0;
    T = n + 2;
    int last = 0;
    for(int i = 1; i <= n; i++) { //第i天至少需要多少个人
        int cur; cin >> cur;
        if(last > cur) add(g, S, i, last - cur, 0); 
        else if(last < cur) add(g, i, T, cur - last, 0); 
        add(g, i, i + 1, INF - cur, 0);
        last = cur;
    }

    add(g, S, n + 1, last, 0);

    for(int i = 1; i <= m; i++) { //第i类人可以工作从第u到第v天，一个的招募费用是c
        int u, v, c;
        cin >> u >> v >> c;
         add(g, v + 1, u, INF, c);
    }

    long long flow = 0, cost = 0;
    EKMin(flow, cost);
    cout << cost << endl;
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
