class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int xo = 0, cnt = 0;
        for(int x : nums) {
            if(x != 0) cnt++;
            xo ^= x;
        }
        if(xo != 0) return nums.size();
        if(cnt == 0) return 0;
        return nums.size() - 1;
    }
};
