#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;  
const int N = 3e5 + 10;

vector<int> g[N];
int to[2 * N], from[2 * N], q[N], fa[N];
int ei = 0;
void add(int u, int v, int i) {
    g[u].push_back(ei); //edge id, query id
    to[ei] = v;
    from[ei] = u;
    q[ei] = i;
    ei++;

    g[v].push_back(ei);
    to[ei] = u;
    from[ei] = v;
    q[ei] = i;
    ei++;
}

string ans[N];
bool vis1[N], vis2[N];
bool vise[N * 2];

void dfs1(vector<int>& deg, int pa, int u) {
    vis1[u] = true;
    for(int ei : g[u]) {
        int v = to[ei];
        if(vise[ei ^ 1]) continue;

        vise[ei] = true;
        if(!vis1[v]) {
            fa[v] = ei;
            dfs1(deg, u, v);
            deg[v]++;
            if(ei % 2 == 0) ans[q[ei]] = "y";
            else ans[q[ei]] = "x";
        } else {
            deg[v]++;
            if(ei % 2 == 0) ans[q[ei]] = "y";
            else ans[q[ei]] = "x";
        }
    }
}

void dfs2(vector<int>& deg, int pa, int u, int pi) {
    vis2[u] = true;
    for(int ei : g[u]) {
        int v = to[ei];
        if(v == pa) continue; //回edge
        if(!vis2[v] && fa[v] == ei) {
            dfs2(deg, u, v, ei);
        }
    }

    if(pa != -1 && deg[u] % 2 == 1) {
        deg[u]--;
        //reverse pi
        deg[pa]++;
        if(pi % 2 == 0) ans[q[pi]] = "x";
        else ans[q[pi]] = "y";
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> e;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v, i);
        e.push_back({u, v});
    }

    memset(vis1, 0, sizeof vis1);
    memset(vis2, 0, sizeof vis2);
    memset(vise, 0, sizeof vise);
    vector<int> deg(n + 1);
    for(int i = 1; i <= n; i++) {
        if(!vis1[i] && g[i].size() > 0) {
            dfs1(deg, -1, i);

            dfs2(deg, -1, i, -1);
        }
    }
    
    vector<int> t(n + 1);
    for(int i = 0; i < m; i++) {
        if(ans[i][0] == 'x') {
            int u = e[i].first;
            if(t[u] == 0) ans[i] = "x+";
            else ans[i] = "x-";
            t[u] ^= 1;
        } else {
            int u = e[i].second;
            if(t[u] == 0) ans[i] = "y+";
            else ans[i] = "y-";
            t[u] ^= 1;
        }
    }
    
    //int c = 0;
    //for(int i = 1; i <= n; i++) c += t[i];
    //cout << c << endl;
    
    for(int i = 0; i < m; i++) cout << ans[i] << endl;
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
