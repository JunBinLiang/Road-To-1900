//https://www.lanqiao.cn/problems/19707/learning/?page=1&first_category_id=1&tags=%E6%A0%91%E4%B8%8A%E5%B7%AE%E5%88%86&tag_relation=intersection
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
int a[N];
vector<int> g[N];

int depth[N], fa[N][18];
int LCA(int x,int y) {
    if(depth[x] < depth[y]){
      swap(x, y);
    }
  
    for(int i = 17; i>=0; i--) {
      if(fa[x][i] != -1 && depth[fa[x][i]] >= depth[y]) {
        x = fa[x][i];
      }
    }
  
    if(x == y) return x;
    for(int i = 17; i >= 0; i--) {
      if(fa[x][i] != fa[y][i]) {                    
        x = fa[x][i];
        y = fa[y][i];
      }
    }
    return fa[x][0];
}

void init(int n) {
    for(int i = 1; i < 18; i++){//construc sparse table
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
  

int cnt[N];

void dfs1(int pa, int u) {
    if(pa != -1) {
        cnt[u] += cnt[pa];
    }
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs1(u, v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(fa, -1, sizeof fa);
    dfs(-1, 1, 0);
    init(n);

    vector<pair<int, int>> q;
    vector<int> ans(m);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        q.push_back({u, v});
    }

    for(int c = 1; c <= 20; c++) {
        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= n; i++) {
            if(a[i] == c) {
                cnt[i] = 1;
            }
        }
        dfs1(-1, 1);
        for(int i = 0; i < m; i++) {
            int u = q[i].first, v = q[i].second;
            if(depth[u] < depth[v]) swap(u, v);
            int lca = LCA(u, v);
            int s = cnt[u];
            if(fa[lca][0] != -1) {
                s -= cnt[fa[lca][0]];
            }
            if(v != lca) {
                s += cnt[v];
                s -= cnt[lca];
            }
            if(s) ans[i]++;
        }
    }

    for(int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
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
