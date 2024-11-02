#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int N = (3010) * 5, M = 2e5 + 10;
long long INF = 1e16;
int n, m, S, T;
long long f[M]; //流量
int to[M];
int d[N], cur[N]; //分层图

struct E {
    int v, ei;
};
vector<E> g[N];
int ei = 0;
void add(vector<E> g[N], int u, int v, int w) {
    //cout << "add " << u << " " << v << " " << w << endl;
    g[u].push_back({v, ei});
    to[ei] = v;
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

long long find(int u, long long limit) {
    if (u == T) return limit;
    long long flow = 0;
    for (int i = cur[u]; i < g[u].size() && flow < limit; i++) {
        int v = g[u][i].v;
        cur[u] = i;  // 当前弧优化
        if (d[v] == d[u] + 1 && f[g[u][i].ei]) {
            long long t = find(v, min(f[g[u][i].ei], limit - flow));
            if (!t) d[v] = -1;
            f[g[u][i].ei] -= t, f[g[u][i].ei ^ 1] += t, flow += t;
        }
    }
    return flow;
}

long long dinic() {
    long long r = 0, flow;
    while (bfs()) while (flow = find(S, INF)) r += flow;
    return r;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    vector<int> g1(n + 1, -1), g2(n + 1, -1); //group
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> c(a.begin(), a.end());
    vector<int> d(b.begin(), b.end());
    
    //vector<int> A(a.begin(), a.end());
    //vector<int> B(b.begin(), b.end());


    S = 0; 
    T = 4 * n + 1;
    int id = n + 1;

    for(int i = 1; i <= n; i++) {
        if(a[i] == i) {
            if(g1[a[i]] == -1) {
                g1[a[i]] = id++;
            }
        } else {
            while(a[i] != i) {
                g1[a[i]] = id;
                swap(a[i], a[a[i]]);
            }
            g1[a[i]] = id;
            id++;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(b[i] == i) {
            if(g2[b[i]] == -1) {
                g2[b[i]] = id++;
            }
        } else {
            while(b[i] != i) {
                g2[b[i]] = id;
                swap(b[i], b[b[i]]);
            }
            g2[b[i]] = id;
            id++;
        }
    }

    map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        mp[g1[a[i]]]++;
        mp[g2[b[i]]]++;
    } //Count group frequency

    set<int> s;
    for(int i = 1; i <= n; i++) {
        if(s.find(g1[a[i]]) == s.end()) {
            add(g, S, g1[a[i]], mp[g1[a[i]]] - 1);
            s.insert(g1[a[i]]);
        }
        add(g, g1[a[i]], a[i], 1);
        add(g, a[i], g2[a[i]], 1);
    }

    for(int i = 1; i <= n; i++) {
        if(s.find(g2[b[i]]) == s.end()) {
            s.insert(g2[b[i]]);
            add(g, g2[b[i]], T, mp[g2[b[i]]] - 1);
        }
    }


    int flow = dinic();
    vector<int> ans;

    set<int> group2(g2.begin(), g2.end());
    for(int i = 1; i <= n; i++) {
        for(auto& e : g[i]) {
            if(group2.find(to[e.ei]) != group2.end() && f[e.ei] == 0) {
                ans.push_back(i);
            }
        }
    }

    for(int ops : ans) {
        for(int i = 1; i <= n; i++) {
            if(c[i] == ops) {
                swap(c[i], c[ops]);
                break;
            }
        }
        for(int i = 1; i <= n; i++) {
            if(d[i] == ops) {
                swap(d[i], d[ops]);
                break;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        while(c[i] != i) {
            ans.push_back(c[i]);
            swap(c[i], c[c[i]]);
        }
    }

    for(int i = 1; i <= n; i++) {
        while(d[i] != i) {
            ans.push_back(d[i]);
            swap(d[i], d[d[i]]);
        }
    }

    cout << ans.size() << endl;
    for(int x : ans) cout << x <<" ";
    cout << endl;
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
