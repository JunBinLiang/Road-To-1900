class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<int, int> pdp;
        pdp[0] = 1;
        for(int i = 0; i < nums.size(); i++) {
            unordered_map<int, int> dp;
            for(auto it = pdp.begin(); it != pdp.end(); it++) {
                int val = it -> first, cnt = it -> second;
                dp[val + nums[i]] += cnt;
                dp[val - nums[i]] += cnt;
            }
            pdp = dp;
        }
        return pdp[target];
    }
};
