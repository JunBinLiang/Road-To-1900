class Solution {
public:
    int maxAbsoluteSum(vector<int>& a) {
        int ans = 0;
        int mn = 0, mx = 0, s = 0;
        for(int i = 0; i < a.size(); i++) {
            s += a[i];
            ans = max(ans, abs(s - mn));
            ans = max(ans, abs(s - mx));
            mn = min(mn, s);
            mx = max(mx, s);
        }
        return ans;
    }
};
