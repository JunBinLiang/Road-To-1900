class Solution {
public:
    const int MOD = 1e9 + 7;
    int distinctSubseqII(string s) {
        vector<int> dp(26);
        for(int i = 0; i < s.size(); i++) {
            int sum = 0;
            for(int j = 0; j < dp.size(); j++) {
                sum += dp[j];
                sum %= MOD;
            }
            dp[s[i] - 'a'] = 1 + sum;
        }
        int ans = 0;
        for(int i = 0; i < dp.size(); i++) {
            ans += dp[i];
            ans %= MOD;
        }
        return ans;
    }
};
