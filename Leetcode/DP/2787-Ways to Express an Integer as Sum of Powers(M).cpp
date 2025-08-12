class Solution {
public:
    const int MOD = 1e9 + 7;
    int numberOfWays(int n, int x) {
        vector<int> a;
        for(int i = 1; i <= n; i++) {
            long long j = 1;
            for(int k = 0; k < x; k++) {
                j *= i;
            }
            if(j <= n) {
                a.push_back(j);
            }
        }

        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int w : a) {
            for(int j = n; j >= 0; j--) {
                if(j + w <= n) {
                    dp[j + w] += dp[j];
                    dp[j + w] %= MOD;
                }
            }
        }
        return dp.back();
    }
};
