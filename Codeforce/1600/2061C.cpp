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

const int MOD = 998244353;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n); 
    if(a[0] == 0) dp[0] = 1;  
  
    for(int i = 1; i < n; i++) {
        if(i == 1 && a[i] == 1) {
            dp[i] = 1;
        }
        if(i - 1 >= 0 && a[i - 1] == a[i]) {
            dp[i] += dp[i - 1];
            dp[i] %= MOD;
        }

        if(i - 2 >= 0 && a[i - 2] + 1 == a[i]) {
            dp[i] += dp[i - 2];
            dp[i] %= MOD;
        }
    }

    if(n == 1) cout << dp[0] + 1 << endl;
    else cout << (dp[n - 2] + dp[n - 1]) % MOD << endl;
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

