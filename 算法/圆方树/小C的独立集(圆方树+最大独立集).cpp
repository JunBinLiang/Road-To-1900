//https://vjudge.net/problem/%E9%BB%91%E6%9A%97%E7%88%86%E7%82%B8-4316
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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N =  200000 + 1000, INF = 1e8;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], fu[N], fw[N], fe[N], prefix[N], sums[N];
int f[N];
int t = 0, ei = 0;
int newnode;
int n, m;

void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, w, ei++});
    g[v].push_back({u, w, ei++});
}

void add1(vector<E> g[N], int u, int v, int w) { //1 direction
    g[u].push_back({v, w, ei++});
}

void build(int u, int v, int w) { //建圆方树
    int sum = w;
    for(int node = v; node != u; node = fu[node]) {
        prefix[node] = sum;
        sum += fw[node];
    }
    prefix[u] = sums[u] = sum;
    
    //加方点
    newnode++;
    add(g2, u, newnode, 0);
    
    //方点连其它边
    for(int node = v; node != u; node = fu[node]) {
        sums[node] = sum;
        add(g2, newnode, node, min(prefix[node], sum - prefix[node]));
    }
}

void tarjan(int from, int u) {
    dfn[u] = low[u] = ++t;
    for(auto& e : g1[u]) {
        int v = e.v, w = e.w;
        if(!dfn[v]) {
            fu[v] = u, fw[v] = w, fe[v] = e.ei;  // fe[j]存储j由哪条边下来，这样可以处理重边问题。
            tarjan(e.ei, v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) { //bridge, 不在环里，所以要和原来一样加上  
                add(g2, u, v, w);
            }
        } else if(e.ei != (from ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    for(auto& e : g1[u]) { 
        //从u出发的简单环。因为是简单环，他一定会回来.
        //建立环
        int v = e.v, w = e.w;
        if(dfn[u] < dfn[v] && fe[v] != e.ei) { //u 下方的点并且父节点不是u
            build(u, v, w);
        }
    }
}

int dp[N][2]; //not take, take
pair<int, int> cal(vector<vector<int>>& a) {
    if(a.size() == 0) return {0, 0};
    int n = a.size();
    vector<vector<int>> f1(n, vector<int>(2));
    vector<vector<int>> f2(n, vector<int>(2));

    f1[0][0] = a[0][0]; //first one is not taken
    //cout << "gg " << 0 << " " << f1[0][0] << " " << f1[0][1] << endl;
    for(int i = 1; i < n; i++) {
        f1[i][0] = a[i][0] + max(f1[i - 1][0], f1[i - 1][1]);
        f1[i][1] = a[i][1] + f1[i - 1][0];
    }
    
    f2[0][1] = a[0][1]; //first one is taken
    for(int i = 1; i < n; i++) {
        f2[i][0] = a[i][0] + max(f2[i - 1][0], f2[i - 1][1]);
        f2[i][1] = a[i][1] + f2[i - 1][0];
    }
    
    return {f1[n - 1][0], max(f2[n - 1][0], f2[n - 1][1])};
}

void dfs(int pa, int u) {
    for(auto& e : g2[u]) {
        if(e.v == pa) continue;
        dfs(u, e.v);
    }
    if(u <= n) { //圆点
        dp[u][0] = 0;
        dp[u][1] = 1;
        for(auto& e : g2[u]) {
            if(e.v == pa) continue;
            dp[u][0] += max(dp[e.v][0], dp[e.v][1]);
            dp[u][1] += dp[e.v][0];
        }
    } else { //方点。方点的取: 环里的第一个点或者最后一个点被取
        vector<vector<int>> a;
        for(auto& e : g2[u]) {
            if(e.v == pa) continue;
            a.push_back({dp[e.v][0], dp[e.v][1]});
        }
        vector<vector<int>> b(a.begin(), a.end());
        reverse(b.begin(), b.end());
        pair<int, int> p1 = cal(a);
        pair<int, int> p2 = cal(b);
        dp[u][0] = p1.first;
        dp[u][1] = max(p1.second, p2.second);
        //if(u == 11) cout << "gg " << a << endl;
    }
    
    //cout << pa << "  " <<  u << "      |" << dp[u][0] << " "  << dp[u][1] << endl;
} 


/*
求仙人掌的最大独立集
*/

void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(g1, u, v, 1);
    }

    newnode = n + 5;
    t = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(dp, 0, sizeof dp);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(-1, i);
            dfs(-1, i);
            ans += max(dp[i][0], dp[i][1]);
        }
    }
    
    cout << ans << endl;
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
