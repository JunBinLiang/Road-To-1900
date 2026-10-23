class Solution {
public:
    vector<string> createGrid(int n, int m, int k) {
        int r = min(n, 4), c = min(m, 4);
        int tot = r * c;
        for(int st = 0; st < (1 << tot); st++) {
            vector<string> vec(r, string(c, '.'));
            for(int i = 1; i < tot; i++) {
                if((st & (1 << i)) > 0) { // block
                    vec[i / c][i % c] = '#';
                }
            }

            vector<vector<int>> dp = rundp(vec);
            vector<string> ans = build(vec, dp, n, m, k);
            if(ans.size() > 0) {
                return ans;
            }
        }
        return {};
    }

    vector<string> build(vector<string> vec, vector<vector<int>> dp, int n, int m, int k) {
        vector<string> ans(n, string(m, '#'));
        for(int i = 0; i < dp.size(); i++) {
            for(int j = 0; j < dp[0].size(); j++) {
                if(dp[i][j] == k) {
                    for(int r = 0; r <= i; r++) {
                        for(int c = 0; c <= j; c++) {
                            ans[r][c] = vec[r][c];
                        }
                    }
                    int cc = j;
                    while(cc < m) {
                        ans[i][cc] = '.';
                        cc++;
                    }
                    int rr = i;
                    while(rr < n) {
                        ans[rr][m - 1] = '.';
                        rr++;
                    }
                    return ans;
                }
            }
        }
        return {};
    }

    vector<vector<int>> rundp(vector<string> a) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        dp[0][0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] == '#') continue;
                if(i > 0) dp[i][j] += dp[i - 1][j];
                if(j > 0) dp[i][j] += dp[i][j - 1];
            }
        }
        return dp;
    }
};
