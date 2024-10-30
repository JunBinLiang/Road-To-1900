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

const int N = (400 + 10) * 8, M = 2e5 + 100, INF = 1e8;
int n, m, S, T;
int f[M], to[M], weight[M]; //流量
int d[N]; //分层图
int incf[N], pre[N];
bool st[N];

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0; int e = 0;
void add(vector<E> g[N], int u, int v, int cap, int w) {
    //cout << "add " << u << " " << v << endl;
    g[u].push_back({v, ei});
    to[ei] = v;
    weight[ei] = w;
    f[ei++] = cap;
    
    g[v].push_back({u, ei});
    to[ei] = u;
    weight[ei] = -w;
    f[ei++] = 0;
}


bool spfaMax() {//判断是否存在最短增广路
    for(int i = 0; i <= e; i++) { //Number of nodes
        d[i] = -INF;
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
        //cout << "bfs  " << u << endl;
        for(int i = 0; i < g[u].size(); i++) {
            E& e = g[u][i];
            if(f[e.ei] && d[e.v] < d[u] + weight[e.ei]) {
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

void EKMax(int& flow, int& cost) {
    while(spfaMax()) //如果存在最短增广路
    {   
        int t = incf[T]; //记录当前最短增广路的最大流量
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

int a[51][51];

int get(int r, int c) {
    return r * (m + 1) + c;
}


void solve() {
    int a, b;
    cin >> a >> b >> n >> m;
    S = (n + 2) * (m + 2)  + 1;
    T = S + 1;
    e = T + 1;
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            //(i, j) -> (i, j + 1)
            int c; cin >> c;
            int e1 = e++;
            int e2 = e++;
            add(g, e1, e2, 1, c);
            add(g, get(i, j), e1, INF, 0);
            add(g, e1, get(i, j + 1), INF, 0);
            add(g, e2, get(i, j + 1), INF, 0);
        }
    }

    for(int j = 0; j <= m; j++) {
        for(int i = 0; i < n; i++) {
            //(i, j) -> (i + 1, j)
            int c; cin >> c;
            int e1 = e++;
            int e2 = e++;
            add(g, e1, e2, 1, c);
            add(g, get(i, j), e1, INF, 0);
            add(g, e1, get(i + 1, j), INF, 0);
            add(g, e2, get(i + 1, j), INF, 0);
        }
    }

    for(int i = 0; i < a; i++) {
        int k, x, y;
        cin >> k >> x >> y;
        add(g, S, get(x, y), k, 0);
    }

    for(int i = 0; i < b; i++) {
        int k, x, y;
        cin >> k >> x >> y;
        add(g, get(x, y), T, k, 0);
    }
    
    int flow = 0, cost = 0;
    EKMax(flow, cost);
    cout  << cost << endl;
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
