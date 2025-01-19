const int N = 1e5 + 10;
const int MOD = 1e9 + 7;
int dp[N][110];

void reset(int n, int k) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = -1;
        }
    }
}
int k;
class Solution {
public:
    int minMaxSums(vector<int>& a, int K) {
        k = K;
        int n = a.size();
        sort(a.begin(), a.end());
        reset(n, k);
        int ans = 0;
        ans += dfs(a, 0, 0);
        ans %= MOD;
        reverse(a.begin(), a.end());
        reset(n, k);
        ans += dfs(a, 0, 0);
        ans %= MOD;
        return ans;
    }
    
    int dfs(vector<int>& a, int i, int t) {
        if(i >= a.size()) {
            return 0;
        }
        if(dp[i][t] != -1) {
            return dp[i][t];
        }
        
        int ans = 0;
        if(t + 1 <= k) {
            ans += a[i]; //stop
            ans %= MOD;
        }
        ans += dfs(a, i + 1, t);
        ans %= MOD;
        if(t + 1 <= k) {
            ans += dfs(a, i + 1, t + 1);
            ans %= MOD;
        }
        return dp[i][t] = ans;
    }
};
