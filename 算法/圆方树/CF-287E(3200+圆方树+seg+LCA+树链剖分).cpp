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

const int MAX = 400000 + 100;

struct Node {
  int l, r;
  int mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 2000000000};
  tree[id * 2 + 2] = {mid + 1, r, 2000000000};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
    return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

const int N =  2e5 + 100, INF = 1e8;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], cut[N], A[N];
vector<int> stk;
int t = 0, ei = 0;
int newnode;
int n, m, q;

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
                    add(g2, newnode, x, 0);
                    //cout << "add " << newnode << " " << x << endl;
                } while (x != v);
                add(g2, newnode, u, 0);
               // cout << "add " << newnode << " " << u << endl;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}


//树链剖分, LCA
int sz[N], son[N], top[N], ids[N];
int id = 0;
int depth[N], fa[N][21];

map<int, int> mps[N];

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

void init() {
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
    sz[u] = 1;
    depth[u] = h;
    for(auto& e : g2[u]) {
        int nxt = e.v;
        if(nxt == pa) continue;
        if(u > n) {
            mps[u][A[nxt]]++;
        }
        dfs(u, nxt, h + 1);
        sz[u] += sz[nxt];
        if(son[u] == -1) {
            son[u] = nxt;
        } else {
            if(sz[nxt] > sz[son[u]]) {
                son[u] = nxt;
            }
        }
    }
}

void dfs1(int pa, int u, int line) {
    top[u] = line;
    ids[u] = id;
    id++;

    if(u > n && mps[u].size() > 0) {
        auto it = mps[u].begin();
        update(0, ids[u], it -> first);
    }

    if(son[u] == -1) return;
    dfs1(u, son[u], line); //先搜索重儿子
    for(auto& e : g2[u]) {
        int nxt = e.v;
        if(nxt == pa || nxt == son[u]) continue;
        dfs1(u, nxt, nxt); //a new heavy line 轻儿子是每个重链的开头
    }
}

int query_path(int u, int v) {
    int ans = 2e9;
    while(top[u] != top[v]) {
        if(depth[top[u]] < depth[top[v]]) swap(u, v);
        ans = min(ans, query(0, ids[top[u]], ids[u]));
        u = fa[top[u]][0];
    }
    if(depth[u] < depth[v]) swap(u, v);
    ans = min(ans, query(0, ids[v], ids[u]));
    return ans;
}

/*
query : 求u 到 v 所有方点的最小值
*/
void solve() {
    cin >> n >> m >> q;
    memset(A, -1, sizeof A);
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(g1, u, v, 0);
    }

    newnode = n + 5;
    t = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    tarjan(-1, 1);

    tree[0] = {0, newnode + 1, 2000000000};
    build(0);

    memset(fa, -1, sizeof fa);
    memset(son, -1, sizeof son);
    dfs(-1, 1, 0);
    dfs1(-1, 1, 0);
    init();
    
    while(q--) {
        char op;
        cin >> op;
        if(op == 'C') { //change value
            int u, val;
            cin >> u >> val;

            int pa = fa[u][0];
            if(pa > n) { //方点
                mps[pa][A[u]]--;
                if(mps[pa][A[u]] == 0) {
                    mps[pa].erase(A[u]);
                }
                A[u] = val;
                mps[pa][val]++;
                auto it = mps[pa].begin();
                update(0, ids[pa], it -> first);
            } else {
                A[u] = val;
            }

        } else {
            int u, v;
            cin >> u >> v;
            int lca = LCA(u, v);
            int ans = query_path(u, v);
            //cout << lca << "  " << ans <<"  " << u << " " << v << endl; 
            if(lca > n) {
                int pa = fa[lca][0];
                ans = min(ans, A[pa]);
                cout << ans << endl;
            } else {
                cout << min(ans, A[lca]) << endl;
            }
        }
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
