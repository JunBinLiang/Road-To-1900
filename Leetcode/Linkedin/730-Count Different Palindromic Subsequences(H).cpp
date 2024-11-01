int dp[1010][1010][4];
class Solution {
public:
    const int MOD = 1e9 + 7;
    int countPalindromicSubsequences(string s) {
        int n = s.size();
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k < 4; k++) {
                    dp[i][j][k] = 0;
                }
            }
        }
        
        for(int l = n - 1; l >= 0; l--) {
            for(int r = l; r < n; r++) {
                if(l == r) {
                    dp[l][r][s[l] - 'a'] = 1;
                } else {
                    if(l + 1 == r) {
                        if(s[l] == s[r]) {
                            dp[l][r][s[l] - 'a'] = 2;
                        } else {
                            dp[l][r][s[l] - 'a'] = 1;
                            dp[l][r][s[r] - 'a'] = 1;
                        }
                        
                    } else {
                        if(s[l] == s[r]) {
                            int sum = 0;
                            for(int c = 0; c < 4; c++) {
                                dp[l][r][c] = dp[l + 1][r - 1][c];
                                sum += dp[l + 1][r - 1][c];
                                sum %= MOD;
                            }
                            dp[l][r][s[l] - 'a'] = sum + 2;
                        } else {
                            for(int c = 0; c < 4; c++) {
                                if(c == s[l] - 'a') {
                                    dp[l][r][c] = dp[l][r - 1][c];
                                } else if(c == s[r] - 'a') {
                                    dp[l][r][c] = dp[l + 1][r][c];
                                } else {
                                    dp[l][r][c] = dp[l + 1][r - 1][c];
                                }
                            }
                        }
                    }
                    
                }
            }
        }
        
        int ans = 0;
        for(int c = 0; c < 4; c++) {
            ans += dp[0][n - 1][c];
            ans %= MOD;
        }
        return ans;
    }
};
