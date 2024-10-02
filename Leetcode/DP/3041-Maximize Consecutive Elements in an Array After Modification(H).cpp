//3:14 - 3:17
class Solution {
public:
    int maxSelectedElements(vector<int>& a) {
        sort(a.begin(), a.end());
        int mx = a.back();
        vector<int> dp(mx + 10);
        
        for(int i = 0; i < a.size(); i++) {
            dp[a[i] + 1] = max(dp[a[i] + 1], dp[a[i]] + 1);
            dp[a[i]] = max(dp[a[i]], 1 + dp[a[i] - 1]);
        }
        
        int ans = 0;
        for(int i = 0; i < dp.size(); i++) {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
