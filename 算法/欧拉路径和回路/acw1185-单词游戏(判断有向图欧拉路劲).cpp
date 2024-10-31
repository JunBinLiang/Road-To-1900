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


/*
有向图欧拉路劲
*/

void yes() {
    cout << "Ordering is possible." << endl;
}
void no() {
    cout << "The door cannot be opened." << endl;
}

int din[26], dout[26];
int p[26];
bool vis[26];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void solve() {
    memset(din, 0, sizeof din);
    memset(dout, 0, sizeof dout);
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < 26; i++) p[i] = i;

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int d1 = s[0] - 'a', d2 = s[s.size() - 1] - 'a';
        //d1 -> d2
        dout[d1]++;
        din[d2]++;
        int r1 = find(d1), r2 = find(d2);
        if(r1 != r2) p[r1] = r2;
        vis[d1] = vis[d2] = true;
    }

    int a = 0, b = 0;
    for(int i = 0; i < 26; i++) {
        if(din[i] != dout[i]) {
            if(din[i] == dout[i] + 1) {
                a++;
            } else if(din[i] + 1 == dout[i]) {
                b++;
            } else {
                no();
                return;
            }
        }
    }

    bool ok = false;
    if((a == 0 && b == 0) || (a == 1 && b == 1)) {
        ok = true;
    }
    if(!ok) {
        no();
        return;
    }

    //判断是否在同一个连通块
    int r = -1;
    for(int i = 0; i < 26; i++) {
        if(!vis[i]) continue;
        if(r == -1) {
            r = find(i);
        } else if(r != find(i)) {
            no();
            return;
        }
    }
    yes();
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
