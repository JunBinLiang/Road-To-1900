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

增广路：
非匹配点 -> 非匹配边 -> 匹配边 -> 非匹配边 ... -> 非匹配点
最大匹配 = 不存在增广路


最大匹配数 = 最小点覆盖 = 点总数 - 最大独立集合 = 总点数 - 最小路劲覆盖
*/

vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool g[110][110];
bool st[110][110];
pair<int, int> match[110][110];

int n, m;

bool dfs(int r, int c) {
    for(auto& d : dir) {
        int newr = r + d[0], newc = c + d[1];
        if(newr >= 1 && newr <= n && newc >= 1 && newc <= n && !st[newr][newc] && !g[newr][newc]) {
            st[newr][newc] = true;
            pair<int, int> p = match[newr][newc];
            if(p.first == -1 || dfs(p.first, p.second)) {
                match[newr][newc] = {r, c};
                return true;
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x][y] = true;
    }

    memset(match, -1, sizeof match); 
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if((i + j) % 2 == 1 && !g[i][j]) {
                memset(st, false, sizeof st);
                if(dfs(i, j)) ans++;
            }
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
