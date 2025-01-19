const long long INF = 1e18;
long long dp[100010][20];
class Solution {
public:
    long long minCost(int n, vector<vector<int>>& a) {
        vector<pair<int, int>> comb;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i != j) {
                    comb.push_back({i, j});
                }
            }
        }    
        
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j < comb.size(); j++) {
                dp[i][j] = -1;
            }
        }
        
        long long ans = INF;
        for(int i = 0; i < comb.size(); i++) {
            auto [op1, op2] = comb[i];
            ans = min(ans, a[0][op1] + a[n - 1][op2] + dfs(comb, a, 1, i));
        }
        return ans;
    }
    
    bool ok(pair<int, int>& p1, pair<int, int>& p2) {
        return p1.first != p2.first && p1.second != p2.second;
    }
    
    long long dfs(vector<pair<int, int>>& comb, vector<vector<int>>& a, int i, int pre) {
        int n = a.size();
        if(i >= n / 2) {
            return 0; 
        }
        
        if(dp[i][pre] != -1) {
            return dp[i][pre];
        }
        
        long long ans = INF;
        for(int j = 0; j < comb.size(); j++) {
            if(ok(comb[pre], comb[j])) {
                auto [op1, op2] = comb[j];
                ans = min(ans, a[i][op1] + a[n - i - 1][op2] + dfs(comb, a, i + 1, j));
            }
        }
        
        return dp[i][pre] = ans;
    }
    
};
