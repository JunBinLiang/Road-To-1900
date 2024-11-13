class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        return f(nums, upper) - f(nums, lower - 1);
    }
    
    long long f(vector<int>& nums, int k) {
        long long ans = 0;
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        while(l < r) {
            if(nums[l] + nums[r] <= k) {
                ans += (r - l);
                l++;
            } else {
                r--;
            }
        }
        return ans;
    }
};
