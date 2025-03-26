//https://www.lanqiao.cn/problems/352/learning/?page=1&first_category_id=1&tags=%E6%A0%91%E4%B8%8A%E5%B7%AE%E5%88%86&tag_relation=intersection
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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 3e5 + 10;
vector<int> g[N];

int depth[N], fa[N][20];
int LCA(int x,int y) {
    if(depth[x] < depth[y]){
      swap(x, y);
    }
  
    for(int i = 19; i>=0; i--) {
      if(fa[x][i] != -1 && depth[fa[x][i]] >= depth[y]) {
        x = fa[x][i];
      }
    }
  
    if(x == y) return x;
    for(int i = 19; i >= 0; i--) {
      if(fa[x][i] != fa[y][i]) {                    
        x = fa[x][i];
        y = fa[y][i];
      }
    }
    return fa[x][0];
}

void init(int n) {
    for(int i = 1; i < 20; i++){//construc sparse table
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

int ans[N], a[N];
unordered_map<int, int> mps1[N], mps2[N];
vector<int> del1[N], del2[N];

void dfs1(int pa, int u) {
    int w = a[u], d = depth[u];
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs1(u, v);
        if(mps1[v].size() > mps1[u].size()) {
            swap(mps1[v], mps1[u]);
        }
        for(auto it = mps1[v].begin(); it != mps1[v].end(); it++) {
            mps1[u][it -> first] += (it -> second);
        }
    }
    
    for(int v : del1[u]) {
        mps1[u][depth[v]]--;
        if(mps1[u][depth[v]] == 0) {
            mps1[u].erase(depth[v]);
        }
    }

    if(mps1[u].find(d + w) != mps1[u].end()) {
        ans[u] += mps1[u][d + w];
    }
}

//用差分
void dfs2(int pa, int u) {
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs2(u, v);
        if(mps2[v].size() > mps2[u].size()) {
            swap(mps2[v], mps2[u]);
        }
        for(auto it = mps2[v].begin(); it != mps2[v].end(); it++) {
            mps2[u][it -> first] += (it -> second);
        }
    }

    for(int val : del2[u]) {
        mps2[u][val]--;
        if(mps2[u][val] == 0) {
            mps2[u].erase(val);
        }
    }

    int w = a[u];
    //depth[u] - depth[v] = w
    if(mps2[u].find(depth[u] - w) != mps2[u].end()) {
        ans[u] += mps2[u][depth[u] - w];
    }

    //cout << u << "   " << mps2[u] << endl;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(fa, -1, sizeof fa);
    dfs(-1, 1, 0);
    init(n);

    for(int i = 0; i <= n; i++) {
        mps1[i].clear();
        mps2[i].clear();
        del1[i].clear();
        del2[i].clear();
    }
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        
        //u -> lca
        //lca -> v
        del1[lca].push_back(u);
        mps1[u][depth[u]]++;
        

        int len = depth[u] - depth[lca];
        mps2[v][depth[lca] - len]++;
        /*
        mps2[lca][depth[lca]]++;
        del2[lca].push_back(lca);
        */
        if(fa[lca][0] != -1) {
            int p = fa[lca][0];
            del2[p].push_back(depth[lca] - len);
        }
        
    }

    memset(ans, 0, sizeof ans);
    dfs1(-1, 1);
    dfs2(-1, 1);
    
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;

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
