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
题意：给一个不一定联通的无向图，问最少在几个点上设置出口，可以使得任意一个点塌掉都能与一个出口联通

1. 看每个连通块
2. 无割点 -> 只需要两个出口
3. 有割点 -> 缩点(树)。 度数1的点:联通分量里需要一个出口(不是割点的位置)，给每个叶子加一个出口
                       度数大于1的点:无需出口(连接至少两个割点，所以可以到达其它有出口的叶子节点)
*/
const int N = 1010;
vector<int> g[N], dcc[N];
int dfn[N], low[N];
bool cut[N];
vector<int> stk;
int t = 0, dcc_cnt;
int n, m;

void tarjan(int root, int u) {
    dfn[u] = low[u] = ++t;
    stk.push_back(u);

    if (u == root && g[u].size() == 0) { //只有一个点的情况
        dcc_cnt ++ ;
        dcc[dcc_cnt].push_back(u);
        return;
    }

    int cnt = 0;
    for(int v : g[u]) {
        if(!dfn[v]) {
            tarjan(root, v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) { //v 搜不到u 上面，所以u可能是割点
                cnt++;
                if(u != root || cnt > 1) { //cut point
                    cut[u] = true;
                }
                dcc_cnt++;
                int x;
                do {
                    x = stk.back();
                    stk.pop_back();
                    dcc[dcc_cnt].push_back(x);
                } while (x != v);
                dcc[dcc_cnt].push_back(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int testcase = 0;
bool solve() {
    cin >> m;
    if(m == 0) {
        return false;
    }

    for(int i = 0; i < N; i++) {
        g[i].clear();
        dcc[i].clear();
    }
    
    n = -1;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        n = max(n, max(u, v));
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(cut, 0, sizeof cut);
    stk.clear();
    t = 0;
    dcc_cnt = 0;
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i, i);
        }
    }
    

    unsigned long long ways = 1;
    long long ans = 0;
    for(int i = 1; i <= dcc_cnt; i++) {
        int deg = 0;
        for(int& v : dcc[i]) {
            if(cut[v]) deg++;
        }
        
        if(deg == 0) {
            if(dcc[i].size() > 1) {
                ans += 2;
                ways *= dcc[i].size() * (dcc[i].size() - 1) / 2;
            }
            else ans++;
        } else if(deg == 1) {
            ans++, ways *= dcc[i].size() - 1;
        }
        dcc[i].clear(); //clear
    }

    testcase++;
    cout << "Case " << testcase << ": " << ans << " " << ways << endl;
    return true;
}

int main(){
    int t = 1;
    //cin >> t;
    while(solve()) {}
    return 0;
}
