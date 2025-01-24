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
using ll = long long;

const int N = 5000 + 50;
int dp[N][N];
int p[N];
int n, m;

int dfs(vector<pair<int, int>>& a, int i, int zero) {
    if(i >= a.size()) {
        return 0;
    }
    if(dp[i][zero] != -1) return dp[i][zero];
    
    int s = 0;
    if(i > 0) s = p[i - 1];
    int one = s - zero;

    int len = a[i].second;
    int ans = 0;
    if(a[i].first == 1) {
        for(int x = 1; x < len; x++) { //add x zero   y one
            int y = len - x;
            int w = (x) * (x - 1) / 2 + (y) * (y - 1) / 2;
            w += (len * one);
            w += (zero * x);
            ans = max(ans, w + dfs(a, i + 1, zero + x));
        }
    } else {
        for(int x = 0; x <= len; x++) { //add x zero   y one
            int y = len - x;
            int w = len * (len - 1) / 2;
            w += (len * one);
            w += (zero * x);
            ans = max(ans, w + dfs(a, i + 1, zero + x));
        }
    }
    
    //cout << i << "   | " << zero << " " << one << "   " << ans << endl;
    return dp[i][zero] = ans;
}

void solve() {
    cin >> n >> m;
    vector<pair<int, int>> a;
    vector<bool> vis(n + 1);
    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
    }

    vector<pair<int, int>> b;

    if(a.size() > 0 && a[0].first != 1) {
        b.push_back({0, a[0].first - 1});
    }
    if(a.size() == 0) b.push_back({0, n});
    else b.push_back({1, a[0].second - a[0].first + 1});
    for(int i = 1; i < a.size(); i++) {
        if(a[i].first - a[i - 1].second - 1) {
            b.push_back({0, a[i].first - a[i - 1].second - 1});
        }
        b.push_back({1, a[i].second - a[i].first + 1});
    }

    if(a.size() > 0 && a.back().second < n) {
        b.push_back({0, n - a.back().second});
    }
    //for(auto& p : b) cout << p.first << " " << p.second << endl;

    int s = 0;
    for(int i = 0; i < b.size(); i++) {
        s += b[i].second;
        p[i] = s;
    }


    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    
    int ans = dfs(b, 0, 0);
    cout << ans << endl;
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
