class Solution {
public:
    int maxNonDecreasingLength(vector<int>& a, vector<int>& b) {
        //2 ^ n
            
        int n = a.size();
        //dp[i][0] : 考虑i个数，然后他第i个数是a[i]， 包含第i个数的最长的subarray是多少
        //dp[i][1] : 考虑i个数，然后他第i个数是b[i]， 包含第i个数的最长的subarray是多少
        
        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = dp[0][1] = 1;
        for(int i = 1; i < n; i++) {
            //a[i] => dp[i][0]
            dp[i][0] = 1;
            if(a[i] >= a[i - 1]) {
                dp[i][0] = max(dp[i][0], 1 + dp[i - 1][0]);
            }
            if(a[i] >= b[i - 1]) {
                dp[i][0] = max(dp[i][0], 1 + dp[i - 1][1]);
            }
            
            
            //b[i] => dp[i][1]
            dp[i][1] = 1;
             if(b[i] >= a[i - 1]) {
                dp[i][1] = max(dp[i][1], 1 + dp[i - 1][0]);
            }
            if(b[i] >= b[i - 1]) {
                dp[i][1] = max(dp[i][1], 1 + dp[i - 1][1]);
            }
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
        }
        return ans;
    }
};
