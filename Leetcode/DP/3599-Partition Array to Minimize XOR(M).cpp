const int N = 260;
long long dp[N][N];
class Solution {
public:
    int minXor(vector<int>& a, int K) {
        int n = a.size();
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                dp[i][j] = -1;
            }
        }
        return dfs(a, 0, K);
    }

    long long dfs(vector<int>& a, int i, int k) {
        if(i >= a.size()) {
            if(k != 0) {
                return 2000000000000ll;
            }
            return 0;
        }
        if(dp[i][k] != -1) return dp[i][k];
        long long xo = 0;
        long long ans = 2000000000000ll;
        for(int j = i; j < a.size(); j++) {
            xo ^= a[j];
            if(k > 0) {
                ans = min(ans, max(xo, dfs(a, j + 1, k - 1)));
            }
        }
        return dp[i][k] = ans;
    }
};
