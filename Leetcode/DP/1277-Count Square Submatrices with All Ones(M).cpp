class Solution {
public:
    int countSquares(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i - 1][j - 1]) {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
                    ans += dp[i][j];
                }
            }
        }
        return ans;
    }
};




class Solution {
public:
    int countSquares(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size(), ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j]) {
                    if(i && j) {
                        a[i][j] += min(a[i - 1][j - 1], min(a[i - 1][j], a[i][j - 1]));
                    }
                    ans += a[i][j];
                }
            }
        }
        return ans;
    }
};
