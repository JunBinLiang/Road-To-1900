const int MOD = 1e9 + 7;
class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        return (cal(high, zero, one) - cal(low - 1, zero, one) + MOD) % MOD;
    }
    
    int cal(int n, int zero, int one) {
        if(n == 0) {
            return 0;
        }
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            if(i >= zero) {
                dp[i] += dp[i - zero];
            }
            if(i >= one) {
                dp[i] += dp[i - one];
            }
            dp[i] %= MOD;
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += dp[i];
            ans %= MOD;
        }
        
        return ans;
    }
};
