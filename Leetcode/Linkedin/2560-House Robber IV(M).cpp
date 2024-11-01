//:4:03 - 4:06
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int l = 1, r = 1e9;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(nums, k, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
    
    bool ok(vector<int>& nums, int k, int mid) {
        int cnt = 0;
        int last = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] > mid) continue;
            if(last == -1) {
                cnt++;
                last = i;
            } else if(i != last + 1) {
                cnt++;
                last = i;
            }
        }
        return cnt >= k;
    }
};
