class Solution {
public:
    int maxChunksToSorted(vector<int>& a) {
        int n = a.size(), ans = 0;
        int mx = 0;
        for(int i = 0; i < n; i++) {
            mx = max(mx, a[i]);
            ans += (mx == i ? 1 : 0);
        }
        return ans;
    }
};
