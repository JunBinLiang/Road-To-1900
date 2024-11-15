#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  


/*
二分图：

二分图 => 不存在奇树环 => 染色无矛盾 

最大匹配数 = 最小点覆盖 = 点总数 - 最大独立集合 = 总点数 - 最小路劲覆盖
*/

struct E {
    int u, v, w;
    bool operator<(const E& other) {
        return w < other.w;
    }
};

const int N = 3e4 + 10;
vector<int> g[N];
int col[N];
bool dfs(int u) {
    bool ans = true;
    for(int v : g[u]) {
        if(col[v] == -1) {
            col[v] = col[u] ^ 1;
            ans &= dfs(v);
        } else {
            if(col[u] == col[v]){
                return false;
            }
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<E> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].w;
    }

    int ans = -1;
    sort(a.begin(), a.end());
    int l = 0, r = a.back().w;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            col[i] = -1;
        }
        for(int i = 0; i < a.size(); i++) {
            int u = a[i].u, v = a[i].v;
            if(a[i].w > mid) {
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }

        bool ok = true;
        for(int i = 1; i <= n; i++) {
            if(col[i] == -1) {
                col[i] = 0;
                ok &= dfs(i);
            }
        }

        if(ok) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
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
