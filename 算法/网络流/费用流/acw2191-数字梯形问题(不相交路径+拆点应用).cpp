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

const int N = 610 * 2, M = 2e4 + 10, INF = 1e8;
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

/*
费用流：最大流中费用最大/最小值

费用: 所有边 边流量 * 边费用 和

SPFA 不能处理负权回路(原图没有负环就行，不用担心残留网络)

*/

bool spfaMin() {//判断是否存在最短增广路
    for(int i = 0; i < N; i++) { //Number of nodes
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
    for(int i = 0; i < N; i++) { //Number of nodes
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

int ids[21][50];
void solve() {
    cin >> m >> n;
    vector<vector<int>> a;
    int id = 1;
    for(int i = 0; i < n; i++) {
        int t = m + i;
        vector<int> b(t);
        for(int j = 0; j < t; j++) {
            cin >> b[j];
            ids[i][j] = id++;
        }
        a.push_back(b);
    }
    S = 0, T = id * 2 + 1;

    //rule 1
    for(int i = 0; i < n; i++) {
        vector<int>& vec = a[i];
        if(i == 0) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, S, ids[i][j], 1, 0);
            }
        }

        if(i + 1 < n) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], ids[i + 1][j], 1, vec[j]);
                add(g, id + ids[i][j], ids[i + 1][j + 1], 1, vec[j]);
            }
        }

        if(i == n - 1) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], T, 1, vec[j]);
            }
        }
    }
    for(int i = 1; i <= id; i++) add(g, i, id + i, 1, 0);
    int flow = 0, cost = 0;
    EKMax(flow, cost);
    cout << cost << endl;

    //rule 2
    for(int i = 0; i <= id * 2 + 1; i++) g[i].clear();
    for(int i = 0; i < ei; i++) {
        f[i] = 0;
        to[i] = 0;
        weight[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        vector<int>& vec = a[i];
        if(i == 0) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, S, ids[i][j], 1, 0);
            }
        }

        if(i + 1 < n) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], ids[i + 1][j], 1, vec[j]);
                add(g, id + ids[i][j], ids[i + 1][j + 1], 1, vec[j]);
            }
        }

        if(i == n - 1) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], T, INF, vec[j]);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i].size(); j++) {
            if(i == n - 1) {
                add(g, ids[i][j], id + ids[i][j], INF, 0);
            } else {
                add(g, ids[i][j], id + ids[i][j], 2, 0);
            }
        }
    }

    flow = 0; cost = 0;
    EKMax(flow, cost);
    cout << cost << endl;

    //rule 3
    for(int i = 0; i <= id * 2 + 1; i++) g[i].clear();
    for(int i = 0; i < ei; i++) {
        f[i] = 0;
        to[i] = 0;
        weight[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        vector<int>& vec = a[i];
        if(i == 0) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, S, ids[i][j], 1, 0);
            }
        }

        if(i + 1 < n) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], ids[i + 1][j], INF, vec[j]);
                add(g, id + ids[i][j], ids[i + 1][j + 1], INF, vec[j]);
            }
        }

        if(i == n - 1) {
            for(int j = 0; j < vec.size(); j++) {
                add(g, id + ids[i][j], T, INF, vec[j]);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i].size(); j++) {
            if(i == n - 1) {
                add(g, ids[i][j], id + ids[i][j], INF, 0);
            } else {
                add(g, ids[i][j], id + ids[i][j], INF, 0);
            }
        }
    }

    flow = 0; cost = 0;
    EKMax(flow, cost);
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
