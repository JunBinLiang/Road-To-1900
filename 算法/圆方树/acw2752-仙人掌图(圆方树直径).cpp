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

const int N =  1e5 + 100, INF = 1e8;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], fu[N], fw[N], fe[N], prefix[N], sums[N];
int f[N];
int t = 0, ei = 0;
int newnode;
int n, m, ans = 0;

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

int dfs(int pa, int u) {
    int d1 = 0, d2 = 0;
    for(auto& e : g2[u]) {
        int v = e.v;
        if(pa == v) continue;
        int len = dfs(u, v) + e.w;
        if (len >= d1) d2 = d1, d1 = len;
        else if (len > d2) d2 = len;
    }

    f[u] = d1; //maximum length for the current node

    if(u <= n) { //圆点
        ans = max(ans, d1 + d2);
    } else { //方点
        vector<int> a;
        a.push_back(-INF); //需要加上环的代表点保证每两个点的距离相等
        for(auto& e : g2[u]) { //会在方点所在的环里相遇
            if(e.v == pa) continue; 
            a.push_back(f[e.v]);
        }
        int sz = a.size();
        for(int i = 0; i < sz; i++) a.push_back(a[i]);
        //用monoqueue求环里两两最大的直径
        deque<pair<int, int>> mono;
        for(int i = 0; i < a.size(); i++) {
            //a[i] + a[j] + (i - j)
            while(mono.size() > 0 && i - mono.front().second > sz / 2) mono.pop_front(); //因为是两个点之间的最短距离，所以sz / 2
            if(mono.size() > 0) {
                ans = max(ans, a[i] + i + mono.front().first);
            }
            while(mono.size() > 0 && (a[i] - i) >= mono.back().first) {
                mono.pop_back();
            }
            mono.push_back({a[i] - i, i});
        }
    }
    return d1; 
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int u;
        cin >> u;
        for(int i = 1; i < k; i++) {
            int v;
            cin >> v;
            add(g1, u, v, 1);
            u = v;
        }
    }

    newnode = n + 5;
    t = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    tarjan(-1, 1);
    /*
    定义在图上两点之间的距离为这两点之间最短路径的距离。
    定义一个图的直径为这张图相距最远的两个点的距离。
    找直径
    */
    dfs(-1, 1);
    cout << ans << endl;
    
}

int main(){
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
