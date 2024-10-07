#include <bits/stdc++.h>
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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 510;
vector<pair<int, int>> g[N];

bool spfa(int n) {
    vector<int> dist(n + 1);
    vector<int> cnt(n + 1);
    vector<bool> vis(n + 1);
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        dist[i] = 0;
        vis[i] = true;
        q.push(i);
    }

    while(q.size()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto& p : g[u]) {
            int v = p.first, w = p.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return true;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }

            }
        }
    }
    return false;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 0; i <= n; i++) {
        g[i].clear();
    }
    
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for(int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, -w});
    }

    if(spfa(n)) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
