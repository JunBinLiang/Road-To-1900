class Solution {
public:
    int mincostTickets(vector<int>& a, vector<int>& costs) {
        const int INF = 1e9;
        vector<int> dp(a.size() + 1, INF);
        dp[0] = 0;
        for(int i = 1; i <= a.size(); i++) {
            dp[i] = min(dp[i], dp[i - 1] + min(costs[0], min(costs[1], costs[2])));
            for(int j = i - 1; j >= 1; j--) {
                if(a[i - 1] - a[j - 1] + 1 <= 7) {
                    dp[i] = min(dp[i], costs[1] + dp[j - 1]);
                }
                if(a[i - 1] - a[j - 1] + 1 <= 30) {
                    dp[i] = min(dp[i], costs[2] + dp[j - 1]);
                }
            }
        }
        return dp.back();
    }
};
