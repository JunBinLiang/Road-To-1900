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
欧拉路劲/回路 (边得联通)
路径: 每条边经过一次。
回路：每条边经过一次并回到原点。


无向图
欧拉路劲存在必要条件: 所有度数为奇数的点只能有0 或者 2 个。 (从奇数点开始搜)
欧拉回路存在必要条件: 所有度数为奇数的点只能有0。 (可以从任何点搜)


有向图：
欧拉路劲存在必要条件: 所有点入度等于出度 或者 除两个点所有点入度等于出度，两个点一个满足出度比入度多1一个满足入度比出度多1
欧拉回路存在必要条件: 所有点入度等于出度 (可以从任何点搜)

必要条件: 在充分条件下，是否可以有种方式一定可以构造一个方案。(是的)


注意:我们需要把搜索的边删除掉。如果是无向图，需要删掉反向边

*/
const int N = 510, M = 4e5 + 100;
int to[M];
int cur[N]; //删边操作
int din[N], dout[N];
bool used[M];
int ans[M];


set<pair<int, int>> g[N];
int ei = 0;
void add(int u, int v) {
    g[u].insert({v, ei});
    to[ei] = v;
    ei++;
}

int type;
int cnt = 0;
void dfs(int u) {
    while(g[u].size() > 0) {
        pair<int, int> p = (*g[u].begin());
        int v = p.first, eid = p.second;
        if(used[eid]) {
            g[u].erase(p);
            continue;
        }
        
        used[eid] = true;
        //删除反向边
        used[eid ^ 1] = true;
        dfs(v);
        ans[cnt++] = eid;
    }
}

/*
无向图欧拉路劲最小路劲表示
*/

void solve() {
    int m;
    cin >> m;
    memset(din, 0, sizeof din);
    memset(dout, 0, sizeof dout);
    memset(used, 0, sizeof used);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
        dout[u]++;
        din[v]++;
    }

    int start = -1;
    for(int i = 1; i <= 500; i++) {
        if((din[i] + dout[i]) % 2 == 1) {
            start = i;
            break;
        }
    }
    
    if(start == -1) {
        for(int i = 1; i <= 500; i++) {
            if(din[i] + dout[i]) {
                start = i;
                break;
            }
        }
    }

    dfs(start);
    cout << to[ans[m - 1] ^ 1] << endl;
    for(int i = m - 1; i >= 0; i--) {
        cout << to[ans[i]] << endl;
    }
    
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
