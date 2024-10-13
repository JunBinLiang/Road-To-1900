//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4320
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

const int N =  1e6 + 100, INF = 1e8;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], cut[N];
vector<int> stk;
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


void tarjan(int root, int u) {
    dfn[u] = low[u] = ++t;
    stk.push_back(u);
    
    int cnt = 0;
    for(auto& e : g1[u]) {
        int v = e.v;
        if(!dfn[v]) {
            tarjan(root, v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) { //v 搜不到u 上面，所以u可能是割点
                cnt++;
                if(u != root || cnt > 1) { //cut point
                    cut[u] = true;
                }
                int x;
                newnode++;
                do {
                    x = stk.back();
                    stk.pop_back();
                    add(g2, newnode, x, 1);
                } while (x != v);
                add(g2, newnode, u, 1);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int depth[N], fa[N][21];
int d[N];
int LCA(int x,int y) {
  if(depth[x] < depth[y]){
    swap(x, y);
  }
  for(int i = 20; i>=0; i--) {
    if(fa[x][i] != -1 && depth[fa[x][i]] >= depth[y]) {
      x = fa[x][i];
    }
  }

  if(x == y) return x;
  for(int i = 20; i >= 0; i--) {
    if(fa[x][i] != fa[y][i]) {                    
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  return fa[x][0];
}

void dfs(int pa, int u) {
    fa[u][0] = pa;
    for(auto& e : g2[u]) {
        if(e.v == pa) continue;
        depth[e.v] = depth[u] + 1;
        if(e.v <= n) {
            d[e.v] = d[u] + 1;
        } else {
            d[e.v] = d[u];
        }
        dfs(u, e.v);
    }
}

void init() {
  for(int i = 1; i < 21; i++){//construc sparse table
    for(int j = 1; j <= n; j++){
      int parent = fa[j][i - 1];
      if(parent == -1) continue;
      fa[j][i] = fa[parent][i - 1];
    }
  }
}

/*
题意：一个图，每一次询问两个点的所有路径的交集的大小（对于一条路径，不能走过同样的点)。看样例

必经点数==圆方树上两点路径上圆点数
*/
void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(g1, u, v, 1);
    }

    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(cut, 0, sizeof cut);
    stk.clear();
    t = 0;
    newnode = n + 5;
    tarjan(1, 1);

    depth[1] = 0;
    d[1] = 1;
    memset(fa, -1, sizeof fa);
    dfs(-1, 1);
    init();
    
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(depth[u] > depth[v]) {
            swap(u, v); 
        }
        int lca = LCA(u, v);
        int s = d[u] + d[v] - 2 * d[lca];
        if(lca <= n) s++;
        cout << s << endl;
    }
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
