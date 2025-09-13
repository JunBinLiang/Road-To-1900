#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int MOD = 1e9 + 7;
vector<pair<long long, long long>> dp;

long long dfs(int k, int cur) {
    if(k == 0) {
        return 1;
    }
    long long ans = 1;
    ans *= cur;
    ans %= MOD;
    k--;
    for(int i = 1; i < min(cur, (int)(dp.size())); i++) {
        if(k >= dp[i].first) {
            k -= dp[i].first;
            ans *= dp[i].second;
            ans %= MOD;
        } else {
            ans *= dfs(k, i);
            ans %= MOD;
            break;
        }
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    dp.clear();
    dp.push_back({0, 0}); // place holder
    dp.push_back({1, 1});
    for(int i = 2; i <= 40; i++) {
        long long p = 1;
        p *= i;
        for(int j = 1; j < i; j++) {
            p *= dp[j].second;
            p %= MOD;
        }
        dp.push_back({1ll << (i - 1), p});
    }
    
    //for(auto p : dp) cout << p.first << "  " << p.second << endl;
    //cout << endl;

    long long ans = 1;
    for(int i = 0; i < a.size() && k > 0; i++) {
        if(a[i] >= dp.size()) {
            ans *= dfs(k, a[i]);
            ans %= MOD;
            break;
        }
        pair<long long, long long> p = dp[a[i]];
        if(k > p.first) {
            k -= p.first;
            ans *= p.second;
            ans %= MOD;
        } else {
            ans *= dfs(k, a[i]);
            ans %= MOD;
            break;
        }
    }
    cout << ans << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
