class Solution {
public:
    const long long INF = 1e18;
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(nums[mid] > get(nums, mid - 1) && nums[mid] > get(nums, mid + 1)) {
                return mid;
            }
            if(nums[mid] < get(nums, mid - 1)) {
                //decreasing
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return -1;
    }
    
    long long get(vector<int>& nums, int i) {
        if(i < 0 || i >= nums.size()) {
            return -INF;
        }
        return nums[i];
    }
};
