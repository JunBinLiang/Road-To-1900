namespace Combination {
    const int MOD = 1e9 + 7;
    int C[2010][2010];
    bool isInit = false;
    
    long long fpow(long long x, int y){
    	long long res = 1;
    	while(y){
    		if(y & 1) res = (res * x) % MOD;
    		x = (x * x) % MOD;
    		y >>= 1;
    	}
	    return res;
    } 
    
    void init() {
        if(isInit) return;
        isInit = true;
        C[0][0] = 1;
        for(int i = 1;i <= 2000; i++) {
          C[i][0]=1;
          for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
          }
        }
    }
}
using namespace Combination;
class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        long long ans = 0;
        vector<vector<long long>> dp(n + 1, vector<long long>(min(n, x) + 1, 0)); //dp[i][j] : ways to place i people with j bands
        
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int band = 1; band <= min(i, x); band++) {
                dp[i][band] += (dp[i - 1][band - 1] * (x - band + 1)); //new band
                dp[i][band] %= MOD;
                dp[i][band] += (dp[i - 1][band] * band); //add on old band
                dp[i][band] %= MOD;
            }
        }

        for(int band = 1; band <= min(n, x); band++) {
            long long w1 = fpow(y, band);
            w1 %= MOD;
            w1 *= dp[n][band];
            w1 %= MOD;
            ans += w1;
            ans %= MOD;
        }
        return ans;
    }
};
