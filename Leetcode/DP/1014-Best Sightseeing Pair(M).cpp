class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& a) {
        int ans = -1e9;
        int mx = a[0] + 0;
        for(int i = 1; i < a.size(); i++) {
            ans = max(ans, mx + a[i] - i);
            mx = max(mx, a[i] + i);
        }
        return ans;
    }
};
