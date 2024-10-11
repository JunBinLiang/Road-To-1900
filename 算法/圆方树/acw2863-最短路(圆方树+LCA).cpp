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

const int N =  20000 + 100;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], fu[N], fw[N], fe[N], prefix[N], sums[N];
int t = 0, ei = 0;
int newnode;

void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, w, ei++});
    g[v].push_back({u, w, ei++});
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

//DO LCA
int depth[N], fa[N][14];
int d[N]; 
int X, Y;
int LCA(int x,int y) {
  if(depth[x] < depth[y]){
    swap(x, y);
  }
  for(int i = 13; i>=0; i--) {
    if(fa[x][i] != 0 && depth[fa[x][i]] >= depth[y]) {
      x = fa[x][i];
    }
  }
  if(x == y) return x;
  for(int i = 13; i >= 0; i--) {
    if(fa[x][i] != fa[y][i]) {                    
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  X = x, Y = y;
  return fa[x][0];
}


void init() {
  for(int i = 1; i < 14; i++){//construc sparse table
    for(int j = 0; j < N; j++){
      int parent = fa[j][i - 1];
      if(parent == -1) continue;
      fa[j][i] = fa[parent][i - 1];
    }
  }
}

void dfs(int pa, int u) { //dfs for LCA
    fa[u][0] = pa;
    for(auto& e : g2[u]) {
        int v = e.v, w = e.w;
        if(v != pa) {
            d[v] = d[u] + w;
            depth[v] = depth[u] + 1;
            dfs(u, v);
        }
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(g1, u, v, w);
    }

    newnode = n + 5;
    t = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    tarjan(-1, 1);
    
    depth[1] = 0;
    d[1] = 0;
    memset(fa, -1, sizeof fa);
    dfs(-1, 1);
    init();
    
    for(int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        if(lca <= n) { //圆点
            cout << d[u] + d[v] - d[lca] * 2 << endl;
        } else { //方点
            int da = d[u] - d[X], db = d[v] - d[Y];
            int l = abs(prefix[X] - prefix[Y]);
            int res = da + db + min(l, sums[X] - l);
            cout << res << endl;
        }
    }
}

int main(){
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
