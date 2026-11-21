const int INF = 1e6;
int dp[2510][2510][2][2];
class Solution {
public:
    int almostPalindromic(string s) {
        int n = s.size();
        for(int l = 0; l < n; l++) {
            for(int r = 0; r < n; r++) {
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        dp[l][r][i][j] = -1;
                    }
                }
            }
        }

        int ans = dfs(s, 0, n - 1, 0, 1);
        return ans;
    }

    int dfs(string& s, int l, int r, int on, int t) {
        if(l >= r) {
            if(l == r && t == 1) {
                return 1;
            }

            if(on == 0 || t != 0) {
                return -INF;
            }
            if(l == r) {
                return 1;
            }
            return 0;
        }
        if(dp[l][r][on][t] != -1) {
            return dp[l][r][on][t];
        }

        int ans = -INF;
        if(on == 1) { //start palindrom
            if(s[l] == s[r]) {
                int g = dfs(s, l + 1, r - 1, 1, t);
                ans = max(ans, 2 + dfs(s, l + 1, r - 1, 1, t));
            }
            if(t > 0) {
                ans = max(ans, 1 + dfs(s, l + 1, r, 1, 0));
                ans = max(ans, 1 + dfs(s, l, r - 1, 1, 0));
            }
        } else {
            ans = max(ans, dfs(s, l + 1, r, 0, t));
            ans = max(ans, dfs(s, l, r - 1, 0, t));
            //start palindrom
            ans = max(ans, dfs(s, l, r, 1, t));
        }
        return dp[l][r][on][t] = ans;
    }
};
