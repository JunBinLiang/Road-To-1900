#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
const int MOD = 998244353;

const int N = 1e6 + 100;
long long fact[N];

long long fpow(long long x, int y){
    long long res = 1;
    while(y){
    	if(y & 1) res = (res * x) % MOD;
    	x = (x * x) % MOD;
    	y >>= 1;
    }
	return res;
} 

long long C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    if(k >= n) {
        cout << fpow(3, n - 1) << endl;
        return;
    }
    
    if(k == 1) {
        cout << 1 << endl;
        return;
    }

    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    vector<long long> dp(n + 1), pdp(n + 1);  
    dp[1] = 2;
    pdp[1] = 2;
    for(int i = 2; i <= n - 1; i++) {
        if(i >= k) {
            dp[i] = (pdp[i - 1] - pdp[i - k] + MOD) % MOD;
        } else {
            dp[i] = pdp[i - 1] + 2;
            dp[i] %= MOD;
        }
        pdp[i] = pdp[i - 1] + dp[i];
        pdp[i] %= MOD;
    }  

    long long ans = 0;
    for(int i = 0; i <= n - 1; i++) {
        long long w = C(n - 1, n - 1 - i);
        ans += (dp[i] * w);
        ans %= MOD;
        //cout << i << "  " << dp[i] <<"  " << w << endl;
    }
    cout << (ans + 1) % MOD << endl;
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
