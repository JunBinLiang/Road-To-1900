//6:12 - 6:15
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int k) {
        map<int, int> f;
        for(int i = 0; i < nums.size(); i++) {
            int m = nums[i] % k;
            if(m < 0) m += k;
            f[m]++;
        }
        
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i <= n; i++) {
            if(f[i % k] > 0) {
                f[i % k]--;
                ans = i + 1;
            } else {
                break;
            }
        }
        return ans;
    }
};
