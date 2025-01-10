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

int dp[20][(1 << 20) + 100];
vector<int> add;
vector<vector<int>> dis;
int dfs(int n, int pre, int st) {
    if(st == 0) {
        return add[pre];
    }
    if(dp[pre][st] != -1) {
        return dp[pre][st];
    }
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        if(st & (1 << i)) {
            ans = min(ans, dis[pre][i] + 1 + dfs(n, i, st ^ (1 << i)));
        }
    }
    return dp[pre][st] = ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, char>> a;
    add = vector<int>(n);
    dis = vector<vector<int>>(n, vector<int>(n));
    for(int i = 0; i < m; i++) {
        int j; char op;
        cin >> j >> op;
        j--;
        a.push_back({j, op});
        if(op == '+') {
            add[j]++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            int cnt = 0;
            for(auto [index, op] : a) {
                if(index == i) { //left
                    if(op == '+') {
                        cnt++;
                    }
                } else if(index == j) { //right
                    if(op == '-') {
                        cnt--;
                    }
                }
                dis[i][j] = max(dis[i][j], cnt);
            }
            //cout << i << " " << j << " " << dis[i][j] << endl;
        }
    }

    memset(dp, -1, sizeof dp);
    int ans = 1e9;
    for(int i = 0; i < n; i++) {
        ans = min(ans, 1 + dfs(n, i, ((1 << n) - 1) ^ (1 << i)));
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
