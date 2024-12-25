#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct CartesianTree {
    vector<int> ls, rs;
    int build(vector<long long>& a) { //用stack 维护树的右链
        int n = a.size() - 1;
        ls = vector<int>(n + 1, 0);
        rs = vector<int>(n + 1, 0);
        vector<int> stk;
        
        for(int i = 1; i <= n; i++) {
            int top = 0;
            while(stk.size() > 0 && a[stk.back()] > a[i]) {
                top = stk.back();
                stk.pop_back();
            }
            if(stk.size() > 0){
                rs[stk.back()] = i;
            }
            if(top != 0){
                ls[i] = top;
            }
            stk.push_back(i);
        }
        
        while(stk.size() > 1) stk.pop_back();
        int root = stk.back();
        return root;
    }
} tr;

const int N = 2e5 + 100;
long long dp[N][63];
long long g[63];
const long long INF = 2e18;
void dfs(vector<long long>& a, vector<long long>& b, int u) {
    //cout << u << endl;
    if(tr.ls[u] != 0) dfs(a, b, tr.ls[u]);
    if(tr.rs[u] != 0) dfs(a, b, tr.rs[u]);
    //for(int i = 0; i <= 62; i++) g[i] = INF;
    
    //merge
    if(tr.ls[u] != 0 || tr.rs[u] != 0) {
        for(int i = 0; i <= 62; i++) {
            for(int j = 0; j + i <= 62; j++) {
                dp[u][i + j] = min(dp[u][i + j], max(a[u], max(dp[tr.ls[u]][i], dp[tr.rs[u]][j])));
            }
        }
    } else {
        dp[u][0] = a[u];
    }

    for(int i = 1; i <= 62; i++) {
        dp[u][i] = min(dp[u][i], (dp[u][i - 1] - 1) / b[u] + 1);
    }

}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 63; j++) {
            if(i == 0) dp[i][j] = 0;
            else dp[i][j] = INF;
        }
    }

    int u = tr.build(b);
    dfs(a, b, u);
    for(int i = 0; i <= 62; i++) {
        if(dp[u][i] == 1) {
            cout << i << endl; 
            break;
        }
    }
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
