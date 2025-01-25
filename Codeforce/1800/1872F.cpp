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
using ll = long long;
const long long INF = 1e9;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), c(n + 1);
    vector<vector<int>> g(n + 1);
    vector<int> in(n + 1);
    vector<int> ans;
    vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        g[i].push_back(a[i]);
        in[a[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(!in[i]) {
            q.push(i);
        }
    }

    while(q.size()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        vis[u] = true;
        for(int v : g[u]) {
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }

    for(int i = 1; i <= n; i++) { //due with cycle
        if(vis[i]) continue;
        int j = i;
        vector<int> p;
        int mn = c[j];
        while(!vis[j]) {
            mn = min(mn, c[j]);
            p.push_back(j);
            vis[j] = true;
            j = a[j];
        }

        int index = 0;
        for(int x = 0; x < p.size(); x++) {
            if(c[p[x]] == mn) index = x;
        }
        for(int x = 1; x <= p.size(); x++) {
            ans.push_back(p[(index + x) % p.size()]);
        }
    }

    for(int x : ans) cout << x << " ";
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
