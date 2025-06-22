class Solution {
public:
    vector<int> findCoins(vector<int>& a) {
        int n = a.size();
        vector<int> ans;
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            if(a[i - 1] - dp[i] == 1) {
                ans.push_back(i);
                for(int j = 0; j <= n; j++) {
                    if(j >= i) dp[j] += dp[j - i];
                }
            } else if(a[i - 1] - dp[i] != 0) {
                return {};
            }
        }
        return ans;
    }
};
