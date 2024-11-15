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


最大匹配数 = 最小点覆盖 = 点总数 - 最大独立集合 = 总点数 - 最小路劲点覆盖
最小点覆盖 ：最少的点覆盖所有的边
*/

const int N = 110;
bool g[N][N];
bool st[N];
int match[N];
int n, m, k;

bool dfs(int x) {
    for(int i = 1; i <= m; i++) {
        if(g[x][i] && !st[i]) {
            st[i] = true;
            if(match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

//思路 : 求最小点覆盖
bool solve() {
    cin >> n >> m >> k;
    if(n == 0) return false;
    memset(g, 0, sizeof g);
    memset(match, -1, sizeof match);
        
    for(int i = 0; i < k; i++) {
        int idx, a, b;
        cin >> idx >> a >> b;
        g[a][b] = true;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        memset(st, 0, sizeof st);
        if(dfs(i))ans++;
    }
        
    cout << ans << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(solve()) {}
    return 0;
}
