#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int N = 1000 + 10, M = 1e5 + 10, INF = 1e8;
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

//左 : 数字  右：bit
//最大化左边 + 最小化右边被取到的 => 最大化左边 + 最大化左边没被取到的 => 最大权独立集合
void solve() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    S = 0;
    T = n + 65;
    for(int i = 1; i <= n; i++) {
        add(g, S, i, 1);
        for(int j = 0; j < 61; j++) {
            if(a[i] & (1ll << j)) {
                add(g, i, n + j + 1, INF);
            }
        }
    }

    for(int j = 0; j < 61; j++) {
        add(g, n + j + 1,T, 1);
    }

    int flow = dinic();
    /*int bittaken = 0;
    for(int eid = 0; eid < ei; eid += 2) {
        if(f[eid] == 0 && to[eid] == T) {
            bittaken++;
        }
    }

    int mis = n + 61 - flow;
    int bitnottaken = 61 - bittaken;
    cout << (mis - bitnottaken) - bittaken << endl;*/
    int mis = n + 61 - flow;
    cout << mis - 61 << endl;
    
    //clear
    for(int i = 0; i <= T; i++) {
        g[i].clear();
    }
    for(int i = 0; i <= ei; i++) {
        to[i] = f[i] = 0;
    }
    ei = 0;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
