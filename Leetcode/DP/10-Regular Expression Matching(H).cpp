class Solution {
public:
    bool isMatch(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(t[j - 1] == '.') {
                    dp[i][j] = dp[i][j] | dp[i - 1][j - 1];
                } else if(t[j - 1] == '*') {
                    char c = t[j - 2];
                    dp[i - 1][j] = dp[i - 1][j] | dp[i - 1][j - 2];
                    dp[i][j] = dp[i][j] | dp[i][j - 2];
                    if(c == '.') {
                        for(int k = i; k <= n; k++) {
                            dp[k][j] = dp[k][j] | dp[i - 1][j - 2];
                        }
                    } else {
                        for(int k = i; k <= n; k++) {
                            if(s[k - 1] == c) {
                                dp[k][j] = dp[k][j] | dp[i - 1][j - 2];
                            } else {
                                break;
                            }
                        }
                    }
                } else {
                    if(t[j - 1] == s[i - 1]) {
                        dp[i][j] = dp[i][j] | dp[i - 1][j - 1];
                    }
                }
            }
        }

        /*for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                if(dp[i][j]) cout << 1 << " ";
                else cout << 0 << " ";
            } cout << endl;
        }*/

        return dp.back().back();
    }
};
