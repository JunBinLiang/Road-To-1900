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

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;
vector<int> g[N];
int n, m;
int p[N], col[N];
bool ok = true;

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void dfs(int u) {
    for(int v : g[u]) {
        if(col[v] == -1) {
            col[v] = col[u] ^ 1;
            dfs(v);
        } else {
            if(col[v] == col[u]) {
                ok = false;
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    vector<pair<int, int>> a, b;
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if(c == 1) {
            a.push_back({u, v});
        } else {
            b.push_back({u, v });
        }
    }

    for(int i = 0; i <= n; i++) p[i] = i, col[i] = -1;

    for(auto& pa : a) {
        int u = pa.first, v = pa.second;
        int r1 = find(u), r2 = find(v);
        if(r1 != r2) {
            p[r1] = r2;
        }
    }

    for(auto& pa : b) {
        int u = pa.first, v = pa.second;
        int r1 = find(u), r2 = find(v);
        if(r1 == r2) {
            cout << 0 << endl;
            return;
        }
        g[r1].push_back(r2);
        g[r2].push_back(r1);
    }

    set<int> s;
    for(int i = 1; i <= n; i++) {
        s.insert(find(i));
    }

    vector<int> roots(s.begin(), s.end());
    int group = 0;
    for(int root : roots) {
        if(col[root] == -1) {
            group++;
            col[root] = 0;
            dfs(root);
            if(!ok) {
                cout << 0 << endl;
                return;
            }
        }
    }
    
    long long ans = 1;
    for(int i = 0; i < group - 1; i++) {
        ans *= 2;
        ans %= MOD;
    }
    cout << ans << endl;
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
