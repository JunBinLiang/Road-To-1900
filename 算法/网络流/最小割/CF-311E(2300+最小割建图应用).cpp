#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 20000, M = 100000 + 10, INF = 1e8;
int n, m, S, T;
int f[M]; //流量
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) {
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
            E e = g[u][i];
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
//参考 : https://blog.csdn.net/Casber/article/details/49892505
void solve() {
    int c; //fail and pay if is friend
    cin >> n >> m >> c; 
    S = 0;
    T = n + m + 1;
    vector<pair<int, int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first; //sex
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].second; //cost
    }

    /*
    S : 0
    T : 1

    想办法把cost 变成一个割然后最小化这个cost


    假设一只狗的sex是0，那如果他被变成1归到t这边，那他就需要cost。
    建立:    add(g, S, i, a[i].second)  add(g, i, T, a[i].second)

    人: 
    类似。用INF 去让同类出现在一个集合里
    
    
    */
    for(int i = 1; i <= n; i++) {
        if(a[i].first == 0) { 
            add(g, S, i, a[i].second);
        } else {
            add(g, i, T, a[i].second);
        }
    }

    int tot = 0;
    for(int i = 1; i <= m; i++) {
        int sex, isFriend; cin >> sex;
        int w, t;
        cin >> w >> t;
        tot += w;
        for(int j = 0; j < t; j++) {
            int idx;
            cin >> idx;
            if(sex == 0) {
                add(g, n + i, idx, INF);
            } else {
                add(g, idx, n + i, INF);
            }
        }
        cin >> isFriend;
        if(isFriend == 1) w += c;

        if(sex == 0) {
            add(g, S, n + i, w);
        } else {
            add(g, n + i, T, w);
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
