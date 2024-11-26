#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/*
[0 1]

[0 0 1]
[0 1 0]

[0 0 0 1] 0
[0 0 1 0] 1
[0 1 0 1] 1
[0 1 1 0] 2
[1 0 1 0] 3

*/

const int MOD = 998244353;
const int N = 1e6 + 10;
void solve() {
    int n;
    cin >> n;
    if(n == 2) {
        cout << 1 << endl;
        return;
    }

    if(n == 3) {
        cout << 2 << endl;
        return;
    }

    vector<long long> dp(n + 1);
    long long s = 0;
    dp[0] = 1; //[0 0 1]
    dp[2] = 1; //[0 1 0]
    s += 2;
    for(int i = 4; i <= n; i++) {
        dp[0] = 1; //[0 0 0 0 ... 1]
        dp[i - 1]++; // [0 0 .. 0 0 1 0]
        dp[i - 1] %= MOD;

        dp[i] += s;
        dp[i] %= MOD;

        s += (dp[i] * i);
        s %= MOD;
        s += (i - 1);
        s %= MOD;
    }

    long long ans = 0;
    for(int i = 0; i < dp.size(); i++) {
        ans += dp[i];
        ans %= MOD;
    }
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
