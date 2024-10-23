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

const int N = 1101 * 50 + 10, M = 200000 + 10, INF = 1e8;
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
        for(auto& e : g[u]) {
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

int get(int day, int i) {
    return day * (n + 2) + i;
}

int p[N]; //union find
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

struct Ship {
    int cap;
    vector<int> stations;
} ships[N];

void solve() {
    int k;
    cin >> n >> m >> k;
    S = N - 1, T = N - 2;
    
    for(int i = 0; i <= n + 1; i++) p[i] = i;
    for(int i = 0; i < m; i++) {
        int cap, t;
        cin >> cap >> t;
        ships[i].cap = cap;
        ships[i].stations.clear();
        for(int j = 0; j < t; j++) {
            int station;
            cin >> station;
            if(station == -1) station = 1 + n; //月球
            if(j > 0) {
                int r1 = find(ships[i].stations[j - 1]), r2 = find(station);
                if(r1 != r2) p[r1] = r2;
            }
            ships[i].stations.push_back(station);
        }
    }
    
    if(find(0) != find(n + 1)) cout << 0 << endl; //no solution
    else {
        int day = 0, flow = 0;
        add(g, S, get(0, 0), k);
        add(g, get(0, n + 1), T, INF);
        
        while(true) {
            day++; //current day
            add(g, get(day, n + 1), T, INF);
            
            //stay on the same position
            for(int i = 0; i <= n + 1; i++) {
                add(g, get(day - 1, i), get(day, i), INF);
            }

            //ship, 
            for(int i = 0; i < m; i++) {
                int sz = ships[i].stations.size();
                int a = ships[i].stations[(day - 1) % sz], b = ships[i].stations[day % sz];
                add(g, get(day - 1, a), get(day, b), ships[i].cap);
                //day - 1的对应node 上运行到 day 的node 上
            }
            flow += dinic();
            if (flow >= k) break;
        }
        cout << day << endl;
    }
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
