const long long INF = 1e18;
class Solution {
public:
    long long maxDifference(vector<int>& a) {
        int n = a.size();
        vector<vector<long long>> dp(n, vector<long long>(2, INF));
        return dfs(a, dp, 0, 0);
    }

    long long dfs(vector<int>& a, vector<vector<long long>>& dp, int i, int turn) {
        if(i >= a.size()) {
            return 0;
        }
        if(i == a.size() - 1) {
            if(turn == 0) {
                return a[i];
            }
            return -a[i];
        }

        if(dp[i][turn] != INF) {
            return dp[i][turn];
        }

        long long ans = -INF;
        if(turn == 0) {
            if(a[i] % 3 == 0) {
                ans = max(ans, a[i] + dfs(a, dp, i + 1, 1));
            } else {
                ans = max(ans, a[i] + dfs(a, dp, i + 1, 0));
            }
            if((a[i] + a[i + 1]) % 3 == 0) {
                ans = max(ans, a[i] + a[i + 1] + dfs(a, dp, i + 2, 1));
            } else {
                ans = max(ans, a[i] + a[i + 1] + dfs(a, dp, i + 2, 0));
            }
        } else {
            ans = INF;
            if(a[i] % 3 == 0) {
                ans = min(ans, -a[i] + dfs(a, dp, i + 1, 0));
            } else {
                ans = min(ans, -a[i] + dfs(a, dp, i + 1, 1));
            }
            if((a[i] + a[i + 1]) % 3 == 0) {
                ans = min(ans, -a[i] - a[i + 1] + dfs(a, dp, i + 2, 0));
            } else {
                ans = min(ans, -a[i] - a[i + 1] + dfs(a, dp, i + 2, 1));
            }
        }
        return dp[i][turn] = ans;
    }
};
