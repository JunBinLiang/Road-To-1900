//3:15
int dp1[1010][1010];
int dp2[1010][1010];
class Solution {
public:
    int n;
    int maxCollectedFruits(vector<vector<int>>& a) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans += a[i][i];
        }
        
        memset(dp1, -1, sizeof dp1);
        memset(dp2, -1, sizeof dp2);
        ans += dfs1(a, 0, n - 1);
        ans += dfs2(a, n - 1, 0);
        return ans;
    }
    
    int dfs1(vector<vector<int>>& a, int r, int c) {
        int n = a.size();
        if(r < 0 || r >= n || c < 0 || c >= n) {
            return -1e9;
        }
        if(r == n - 1 && c == n - 1) {
            return 0;
        }
        if(r == c) return -1e9;
        if(dp1[r][c] != -1) return dp1[r][c];
        int ans = -1e9;
        ans = max(ans, a[r][c] + dfs1(a, r + 1, c));
        ans = max(ans, a[r][c] + dfs1(a, r + 1, c - 1));
        ans = max(ans, a[r][c] + dfs1(a, r + 1, c + 1));
        return dp1[r][c] = ans;
    }
    
    int dfs2(vector<vector<int>>& a, int r, int c) {
        int n = a.size();
        if(r < 0 || r >= n || c < 0 || c >= n) {
            return -1e9;
        }
        if(r == n - 1 && c == n - 1) {
            return 0;
        }
        if(r == c) return -1e9;
        if(dp2[r][c] != -1) return dp2[r][c];
        int ans = -1e9;
        ans = max(ans, a[r][c] + dfs2(a, r - 1, c + 1));
        ans = max(ans, a[r][c] + dfs2(a, r, c + 1));
        ans = max(ans, a[r][c] + dfs2(a, r + 1, c + 1));
        return dp2[r][c] = ans;
    }
};
