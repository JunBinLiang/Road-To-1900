#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    

using namespace std;

struct E {
    int u, v, w;
    bool operator<(const E& other) {
        return w < other.w;
    }
};
const int N = 1e6 + 10;
int p[N], fa[N];
vector<int> g[N];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void dfs(int pa, int u) {
    fa[u] = pa;
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<E> e(m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = {u, v, w};
    }

    for(int i = 1; i <= n; i++) {
        p[i] = i;
        fa[i] = -1;
        g[i].clear();
    }

    int index = -1;
    sort(e.begin(), e.end());
    for(int i = m - 1; i >= 0; i--) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        if(r1 == r2) {
            index = i;
        } else {
            p[r1] = r2;
        }
    }

    for(int i = 1; i <= n; i++) p[i]= i;
    for(int i = m - 1; i > index; i--) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int r1 = find(u), r2 = find(v);
        if(r1 == r2) continue;
        p[r1] = r2;
        g[u].push_back(v);
        g[v].push_back(u);
        //cout << "add " << u << " " << v << endl;
    }

    int u = e[index].u, v = e[index].v, w = e[index].w;
    int r = find(u);
    
    //cout << "root " << r << "  " << u << " " << v << endl;
    //return;
    
    dfs(-1, r);

    //Find LCA
    set<int> s;
    while(u != -1) {
        s.insert(u);
        u = fa[u];
    }

    int lca = v;
    while(s.find(lca) == s.end()) {
        lca = fa[lca];
    }

    vector<int> p1, p2;
    u = e[index].u, v = e[index].v;
    while(u != lca) {
        p1.push_back(u);
        u = fa[u];
    }
    while(v != lca) {
        p2.push_back(v);
        v = fa[v];
    }
    p1.push_back(lca);
    
    vector<int> ans(p1.begin(), p1.end());
    for(int i = p2.size() - 1; i >= 0; i--) ans.push_back(p2[i]);
    cout << w << " " << ans.size() << endl;
    for(int ver : ans) cout << ver << " ";
    cout << endl;
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
