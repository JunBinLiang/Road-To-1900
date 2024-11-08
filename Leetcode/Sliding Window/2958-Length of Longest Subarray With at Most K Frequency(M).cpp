class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        map<int, int> mp;
        int ans = 0;
        for(int i = 0, j = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
            while(mp[nums[i]] > k) {
                mp[nums[j]]--;
                if(mp[nums[j]] == 0) mp.erase(nums[j]);
                j++;
            }
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
