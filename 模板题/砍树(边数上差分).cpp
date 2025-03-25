//https://www.lanqiao.cn/problems/3517/learning/?page=1&first_category_id=1&tags=%E6%A0%91%E4%B8%8A%E5%B7%AE%E5%88%86&tag_relation=intersection
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int N = 1e5 + 10;
vector<int> g[N];

int depth[N], fa[N][21];
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

void init(int n) {
    for(int i = 1; i < 21; i++){//construc sparse table
      for(int j = 1; j <= n; j++){
        int parent = fa[j][i - 1];
        if(parent == -1) continue;
        fa[j][i] = fa[parent][i - 1];
      }
    }
}

void dfs(int pa, int u, int h) {
    fa[u][0] = pa;
    depth[u] = h;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v, h + 1);
    }
}

//进行树上边差分
int dif[N];
map<pair<int, int>, int> e;
int ans = -1;
int n, m;
//遍历时统计以每个节点为根的树的节点的权值和，就是当前节点到父亲节点的边的最终权值了
int dfs1(int pa, int u) {
    int s = dif[u];
    for(int v : g[u]) {
        if(pa == v) continue;
        s += dfs1(u, v);
    }

    if(pa != -1) {
        int id = e[{min(pa, u), max(pa, u)}];
        if(s == m) {
            ans = max(ans, id);
        }
    }
    //cout << u << "  " << s << endl;
    return s;
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        if(u > v) swap(u, v);
        e[{u, v}] = i + 1;
    }

    memset(fa, -1, sizeof fa);
    memset(dif, 0, sizeof dif);
    dfs(-1, 1, 0);
    init(n);

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if(depth[u] < depth[v]) swap(u, v);
        int lca = LCA(u, v);
        dif[u]++;
        dif[v]++;
        dif[lca] -= 2;
        //cout << "lca  " << u << " " << v << " " << lca << endl;
    }

    dfs1(-1, 1);
    cout << ans << endl;

}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
