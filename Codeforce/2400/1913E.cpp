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

const int N = (50 * 50 + 10) * 3, M = 2e5 + 10, INF = 1e8;
int n, m, S, T;
int f[M], to[M], weight[M]; //流量
int d[N]; //分层图
int incf[N], pre[N];
bool st[N];

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int cap, int w) {
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
    for(int i = 0; i <= T; i++) { //Number of nodes
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

bool spfaMax() {//判断是否存在最短增广路
    for(int i = 0; i <= T; i++) { //Number of nodes
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

void EKMin(int& flow, int& cost) {
    while(spfaMin()) //如果存在最短增广路
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

int get(int r, int c) {
    return r * m + c;
}

void solve() {
    cin >> n >> m;
    S = n * m + n + m + 1;
    T = S + 1;
    int c = 0;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            c += (a[i][j]); //turn all to zero
        }
    }

    int s1 = 0, s2 = 0;
    for(int i = 0; i < n; i++) {
        int w;
        cin >> w;
        s1 += w;
        add(g, S, n * m + i, w, 0);
    }
    
    for(int i = 0; i < m; i++) {
        int w;
        cin >> w;
        s2 += w;
        add(g, n * m + n + i, T, w, 0);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == 0) {
                add(g, n * m + i, get(i, j), 1, -1);
            } else {
                add(g, n * m + i, get(i, j), 1, 1); //turn back
            }
            add(g, get(i, j), n * m + n + j, 1, 0);
        }
    }

    if(s1 != s2) {
        cout << -1 << endl;
        return;
    }

    int flow = 0, cost = 0;
    EKMax(flow, cost);
    if(flow != s1) cout << -1 << endl;
    else cout << (c - cost) << endl;
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