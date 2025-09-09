class Solution {
public:
    const int MOD = 1e9 + 7;
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        for(int i = 2; i <= n; i++) {
            for(int j = i - delay; j >= max(1, i - forget + 1); j--) {
                dp[i] += dp[j];
                dp[i] %= MOD;
            }
        }

        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(i + forget > n) {
                ans += dp[i];
                ans %= MOD;
            }
        }
        return ans;
    }
};
