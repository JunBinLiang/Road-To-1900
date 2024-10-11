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

/*
题意：删除一个点后可以使图最多有多少个连通块
*/
const int N = 10010;
vector<int> g[N];
int dfn[N], low[N];
int t = 0;
int ans = 0;
void tarjan(int root, int u) {
    dfn[u] = low[u] = ++t;
    int cnt = 0;
    for(int v : g[u]) {
        if(!dfn[v]) {
            tarjan(root, v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                cnt ++ ; //割点,使下面不连通
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(u != root) cnt++;
    ans = max(ans, cnt);
}

bool solve() {
    int n, m;
    cin >> n >> m;
    if(n == 0 && m == 0) {
        return false;
    }

    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    t = 0;
    ans = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(!dfn[i]) {
            cnt++;
            tarjan(i, i);
        }
    }
    cout << cnt + ans - 1 << endl;
    return true;
}

int main(){
    int t = 1;
    //cin >> t;
    while(solve()) {}
    return 0;
}
