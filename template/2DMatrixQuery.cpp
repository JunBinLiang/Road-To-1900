struct MatrixQuery {
  int n, m;
  vector<vector<int>> dp;
  void init(vector<vector<int>>& a) {
    n = a.size();
    m = a[0].size();
    dp = vector<vector<int>>(n + 1, vector<int>(m + 1)); 
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++) {
        dp[i][j] = a[i - 1][j - 1];
        dp[i][j] += dp[i - 1][j];
        dp[i][j] += dp[i][j - 1];
        dp[i][j] -= dp[i - 1][j - 1];
      }
    }
  }

  int query(int r1, int c1, int r2, int c2) {
    r1++;
    c1++;
    r2++;
    c2++;
    return dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
  }
} ma;
