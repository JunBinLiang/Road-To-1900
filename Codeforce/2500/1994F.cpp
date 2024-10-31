#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include<set>
#include<unordered_set>
#include <string.h>


using namespace std;


/*
无向图欧拉回路 => all degree must be even
*/

const int N = 5e5 + 10, M = (5e5 + 10) * 2; 

unordered_set<int> g[N];
vector<int> g1[N];
int to[M];
bool used[M];
int ans[M];
int deg[N];
int ei = 0, cnt = 0;
void add(int u, int v) {
    g[u].insert(ei);
    to[ei] = v;
    ei++;
}

void dfs(int u) {
    while(g[u].size() > 0) {
        int eid = (*g[u].begin());
        if(used[eid]) {
            g[u].erase(eid);
            continue;
        }
        used[eid] = true;
        used[eid ^ 1] = true; //删除反向边
        dfs(to[eid]);
        ans[cnt++] = eid;
    }
}

int dfs1(vector<bool>& vis, int u) {
    vis[u] = true;
    vector<pair<int, int>> b;
    int oddcnt = 0;
    if(deg[u] % 2 == 1) oddcnt = 1;
    for(int v : g1[u]) {
        if(vis[v]) continue;
        int t = dfs1(vis, v);
        if(t) {
            oddcnt++;
            add(u, v);
            add(v, u);
        }
    }
    return oddcnt % 2;
}


void clear(int n) {
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        g1[i].clear();
        deg[i] = 0;
    }
    for(int i = 0; i < ei; i++) {
        used[i] = false;
    }
    cnt = 0;
    ei = 0;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(w == 1) {
            deg[u]++;
            deg[v]++;
            add(u, v);
            add(v, u);
        } else {
            g1[u].push_back(v);
            g1[v].push_back(u);
        }
    }

    vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(deg[i] % 2 == 0 || vis[i]) continue;
        int v = dfs1(vis, i);
        if(v % 2 == 1) {
            cout << "NO" << endl;
            clear(n);
            return;
        }
    }

    //output euler path
    dfs(1);
    cout << "YES" << endl;
    cout << cnt << endl;
    cout << to[ans[cnt - 1] ^ 1] << " ";
    for(int i = cnt - 1; i >= 0; i--) {
        cout << to[ans[i]] << " ";
    }
    cout << endl;
    clear(n);
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
