class Solution {
public:
    const int MOD = 1e9 + 7;
    int numberOfPermutations(int n, vector<vector<int>>& a) {
        sort(a.begin(), a.end());
        if(a[0][0] == 0 && a[0][1] != 0) {
            return 0;
        }
        int INV = 0;
        for(int i = 0; i < a.size(); i++) INV = max(INV, a[i][1]);
        
        vector<vector<int>> dp(n, vector<int>(INV + 1, 0));
        dp[0][0] = 1;
        int idx = 0;
        for(int i = 1; i < n; i++) {
            while(idx < a.size() && a[idx][0] < i) {
                idx++;
            }
            int len = i;
            for(int j = 0; j <= INV; j++) {
                for(int add = 0; add <= len && j + add <= INV; add++) {
                    dp[i][add + j] += dp[i - 1][j];
                    dp[i][add + j] %= MOD;
                }
            }
            
            if(a[idx][0] == i) {
                for(int j = 0; j <= INV; j++) {
                    if(j != a[idx][1]) {
                        dp[i][j] = 0;
                    }
                }
            }
        }
        
        return dp[n - 1][a.back()[1]];
    }
};
