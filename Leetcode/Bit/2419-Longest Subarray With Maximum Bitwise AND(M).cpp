class Solution {
public:
    int longestSubarray(vector<int>& a) {
        int n = a.size();
        int maxv = *max_element(a.begin(), a.end());
        int cnt = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] == maxv) {
                cnt++;
            } else {
                cnt = 0;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};
