class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        int ans = 0;
        for(int l = n - 1; l >= 0; l--) {
            for(int r = l; r < n; r++) {
                if(l == r) {
                    dp[l][r] = 1;
                } else if(l + 1 == r) {
                    if(s[l] == s[r]) dp[l][r] = 2;
                    else dp[l][r] = 1;
                } else {
                    if(s[l] == s[r]) {
                        dp[l][r] = max(dp[l][r], 2 + dp[l + 1][r - 1]);
                    } 
                    dp[l][r] = max(dp[l][r], max(dp[l + 1][r], dp[l][r - 1]));
                }
                ans = max(ans, dp[l][r]);
            }
        }
        return ans;
    }
};
