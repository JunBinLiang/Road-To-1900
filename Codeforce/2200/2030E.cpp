#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

const int MOD = 998244353;
const int N = 2e5 + 10;
int cnt[N];
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
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) cnt[i] = 0;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    if(cnt[0] == 0) {
        cout << 0 << endl;
        return;
    }

    //score of array a : f[0] + min(f[0], f[1]) + min(f[0], f[1], f[2]) ...
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    vector<vector<long long>> dp(cnt[0] + 1, vector<long long>(2));
    for(int i = 0; i <= cnt[0]; i++) {
        long long ways = C(cnt[0], i);
        dp[i][0] = ways;
        dp[i][1] = (ways * i);
        dp[i][1] %= MOD;
        
        //cout << i << "  |" << dp[i][0] << "  " << dp[i][1] << endl;
    }
    //cout << endl;

    for(int i = 1; i <= n; i++) {
        vector<vector<long long>> cur(cnt[i] + 1, vector<long long>(2));

        //with suffix
        vector<long long> vec1(2);
        int idx = dp.size() - 1;
        for(int j = cnt[i]; j >= 0; j--) {
            long long ways = C(cnt[i], j);
            while(idx >= j) {
                vec1[0] += dp[idx][0];
                vec1[0] %= MOD;
                vec1[1] += dp[idx][1];
                vec1[1] %= MOD;
                idx--;
            }
            
            cur[j][0] += (ways * vec1[0]) % MOD;
            
            cur[j][1] += (vec1[1] * ways);
            cur[j][1] %= MOD;
            cur[j][1] += ((vec1[0] * ways) % MOD * j);
            cur[j][1] %= MOD;
        }     

        long long s = 0;
        for(int j = cnt[i]; j >= 0; j--) {
            long long ways = C(cnt[i], j);
            if(j < dp.size()) {
                cur[j][0] += (dp[j][0] * s);
                cur[j][0] %= MOD;
                cur[j][1] += ((dp[j][0] * s) % MOD * j);
                cur[j][1] %= MOD;
                //move old score
                cur[j][1] += (dp[j][1] * s);
                cur[j][1] %= MOD;
            }
            s += ways;
            s %= MOD;
        }
        dp = cur;   
    }

    long long ans = 0;
    for(int i = 0; i < dp.size() ; i++) {
        ans += dp[i][1];
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
