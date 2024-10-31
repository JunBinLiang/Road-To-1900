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
const int N = 1e5 + 100, M = 4e5 + 100;
int to[M];
int cur[N]; //删边操作
int din[N], dout[N];
bool used[M];
int ans[M];


unordered_set<int> g[N];
int ei = 0;
void add(int u, int v) {
    g[u].insert(ei);
    to[ei] = v;
    ei++;
}

int type;
int cnt = 0;
void dfs(int u) {
    while(g[u].size() > 0) {
        int eid = (*g[u].begin());
        if(used[eid]) {
            g[u].erase(eid);
            continue;
        }
        
        used[eid] = true;
        if(type == 1) { //删除有向边
            used[eid ^ 1] = true;
        }

        int t;
        if(type == 1) { //无向图
            t = eid /2 + 1;
            if(eid % 2 == 1) t = -t;  //(0,1) (2,3) (4,5) 奇数编号是返回的边
        } else {
            t = eid + 1;
        }

        dfs(to[eid]);
        ans[cnt++] = t;
    }
}

void solve() {
    memset(din, 0, sizeof din);
    memset(dout, 0, sizeof dout);
    memset(used, 0, sizeof used);

    
    int n, m;
    cin >> type >> n >> m;

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        if(type == 1) {
            add(v, u);
        }
        dout[u]++;
        din[v]++;

    }
    
    if(type == 1) {
        for(int i = 1; i <= n; i++) {
            if((din[i] + dout[i]) % 2 == 1) {
                cout << "NO" << endl;
                return; 
            }
        }
    } else {
        for(int i = 1; i <= n; i++) {
            if(din[i] != dout[i]) {
                cout << "NO" << endl;
                return; 
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(g[i].size()) {
            dfs(i);
            break;
        }
    }

    if(cnt < m) { //not all edge are visited
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for(int i = cnt - 1; i >= 0; i--){
        cout << ans[i] << " ";
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
