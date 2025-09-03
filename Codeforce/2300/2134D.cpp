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

const int N = 2e5 + 100;
vector<int> g[N];
pair<int, int> childs[N];
int h[N];

int dfs(int pa, int u) {
    vector<pair<int, int>> a;
    for(int v : g[u]) {
        if(v == pa) continue;
        int d = dfs(u, v);
        a.push_back({d, v});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    if(a.size() == 0) {
        childs[u] = {-1, -1};
    } else if(a.size() == 1) {
        childs[u] = {a[0].second, -1};
    } else {
        childs[u] = {a[0].second, a[1].second};
    }
    
    if(a.size() == 0) {
        return h[u] = 1;
    } else {
        return h[u] = 1 + a[0].first;
    }
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        childs[i] = {-1, -1};
    }
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(-1, 1);
    int mx = -1, u = -1;
    for(int i = 1; i <= n; i++) {
        int di = 1;
        if(childs[i].first != -1) di += h[childs[i].first];
        if(childs[i].second != -1) di += h[childs[i].second];
        if(di > mx) {
            mx = di;
            u = i;
        }
    }

    if(mx == n) {
        cout << -1 << endl;
        return;
    }

    vector<int> a = {u};
    int u1 = childs[u].first, u2 = childs[u].second;
    while(u1 != -1) {
        a.push_back(u1);
        u1 = childs[u1].first;
    }

    while(u2 != -1) {
        a.push_back(u2);
        u2 = childs[u2].first;
    }
    
    for(int i = 0; i < a.size(); i++) {
        if(g[a[i]].size() > 2) {
            int A = -1, B = -1, C = -1;
            set<int> s(a.begin(), a.end());
            B = a[i];
            for(int v : g[a[i]]) {
                if(s.find(v) != s.end()) {
                    A = v;
                } else {
                    C = v;
                }
            }
            cout << A << " " << B << " " << C << endl;
            break;
        }
    }

}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
