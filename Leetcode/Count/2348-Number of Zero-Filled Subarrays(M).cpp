class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long ans = 0, cnt = 0;
        for(int i = 0; i < nums.size(); i++) {
            ans += (cnt += (nums[i] == 0 ? 1 : -cnt));
        }
        return ans;
    }
};
