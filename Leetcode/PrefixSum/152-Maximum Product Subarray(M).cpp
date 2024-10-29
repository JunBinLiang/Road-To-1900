class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0];
        int p = 1;
        //maximum negative
        //minimum positive
        int pos = -1, neg = 1;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0) {
                p = 1;
                pos = -1;
                neg = 1;
                ans = max(ans, 0);
            } else {
                p *= nums[i];
                ans = max(ans, p);
                if(pos > 0) ans = max(ans, p / pos);
                if(neg < 0) ans = max(ans, p / neg);
                if(p > 0) {
                    if(pos == -1) pos = p;
                    else pos = min(pos, p);
                } else {
                    if(neg == 1) neg = p;
                    else neg = max(neg, p);
                }
            }
        }
        return ans;
    }
};
