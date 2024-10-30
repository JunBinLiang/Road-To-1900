const int N = 5050 + 10, M = 2e5 + 10, INF = 1e8;
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

bool spfaMax() {//判断是否存在最短增广路
    for(int i = 0; i <= 2 * n * n + 2; i++) { //Number of nodes
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
    return r * n + c;
}

class Solution {
public:
    int cherryPickup(vector<vector<int>>& a) {
        n = a.size();
        S = n * n * 2 + 1; T = S + 1;
        
        add(g, S, get(0, 0), 2, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(a[i][j] == -1) continue;
                add(g, get(i, j), n * n + get(i, j), 1, a[i][j]);

                if(i + 1 < n && a[i + 1][j] != -1) {
                    add(g, get(i, j), get(i + 1, j), INF, 0);
                    add(g, n * n + get(i, j), get(i + 1, j), INF, 0);
                }

                if(j + 1 < n && a[i][j + 1] != -1) {
                    add(g, get(i, j), get(i, j + 1), INF, 0);
                    add(g, n * n + get(i, j), get(i, j + 1), INF, 0);
                }
            }
        }
    
        add(g, get(n - 1, n - 1), T, INF, 0);
        add(g, n * n + get(n - 1, n - 1), T, INF, 0);

        int flow = 0, cost = 0;
        EKMax(flow, cost);
        
        //clear
        for(int i = 0; i <= 2 * n * n + 2; i++) g[i].clear();
        for(int i = 0; i < ei; i++) {
            f[i] = to[i] = weight[i] = 0;
        }
        ei = 0;
        return cost;
    }
};
