class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        vector<pair<int, int>> a;
        for(int i = 0; i < nums.size(); i++) {
            a.push_back({nums[i], i});
        }
        sort(a.begin(), a.end());
        
        int ans = 0, mn = a[0].second;
        for(int i = 1; i < a.size(); i++) {
            if(a[i].second > mn) {
                ans = max(ans, a[i].second - mn);
            }
            mn = min(mn, a[i].second);
        }
        return ans;
    }
};
