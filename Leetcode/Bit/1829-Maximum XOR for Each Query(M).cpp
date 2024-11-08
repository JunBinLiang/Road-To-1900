class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int k) {
        vector<int> ans;
        int xo = 0;
        for(int i = 0; i < nums.size(); i++) {
            xo ^= nums[i];
            int x = 0;
            for(int j = 0; j < k; j++) {
                if(xo & (1 << j)) {
                    
                } else {
                    x += (1 << j);
                }
            }
            ans.push_back(x);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
