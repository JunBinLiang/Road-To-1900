class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            dp[i] = dp[i - 1];
            dp[i] = max(dp[i], nums[i] + (i - 2 >= 0 ? dp[i - 2]  : 0));
        }
        return dp.back();
    }
};
