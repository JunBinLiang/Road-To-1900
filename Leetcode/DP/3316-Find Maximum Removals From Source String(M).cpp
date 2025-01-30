const int N = 3010, INF = 1e9;
int dp[N][N];
bool t[N];
class Solution {
public:
    int maxRemovals(string s, string p, vector<int>& a) {
        int n = s.size();
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                dp[i][j] = INF;
            }
        }
        
        for(int i = 0; i <= n; i++) t[i] = false;
        for(int i : a) t[i] = true;
        return dfs(s, p, 0, 0);
    }
    
    int dfs(string& s, string& p, int i, int j) {
        if(i >= s.size()) {
            if(j >= p.size()) {
                return 0;
            } else {
                return -INF;
            }
        }
        if(dp[i][j] != INF) {
            return dp[i][j];
        }
        
        int ans = -INF;
        if(t[i]) {
            ans = max(ans, 1 + dfs(s, p, i + 1, j));
            ans = max(ans, dfs(s, p, i + 1, j));
            if(j < p.size() && s[i] == p[j]) {
                ans = max(ans, dfs(s, p, i + 1, j + 1));
            }
        } else {
            ans = max(ans, dfs(s, p, i + 1, j));
            if(j < p.size() && s[i] == p[j]) {
                ans = max(ans, dfs(s, p, i + 1, j + 1));
            }
        }
        return dp[i][j] = ans;
    } 
};
