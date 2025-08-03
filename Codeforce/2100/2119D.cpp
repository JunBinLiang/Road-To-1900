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

void solve() {
    int n, MOD;
    cin >> n >> MOD;

    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2));
    dp[1][1] = 1;
    dp[1][0] = 2;
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= i - 1; j++) {
            //take cur, set to 0
            dp[i][j + 1] += (dp[i - 1][j] * i);
            dp[i][j + 1] %= MOD;
            //take cur, set to 1
            dp[i][j] += (dp[i - 1][j] * i * (j + 1));
            dp[i][j] %= MOD;

            //not take set to 0
            dp[i][j] += dp[i - 1][j];
            dp[i][j] %= MOD;
            //not take set to 1
            if(j) {
                dp[i][j - 1] += (dp[i - 1][j] * j);
                dp[i][j - 1] %= MOD;
            }
        }
    }

    cout << dp[n][0] << endl;
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
