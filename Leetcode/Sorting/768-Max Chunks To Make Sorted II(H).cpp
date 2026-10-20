class Solution {
public:
    int maxChunksToSorted(vector<int>& a) {
        int n = a.size(), ans = 0;
        vector<int> lmin(n);
        for(int i = n - 1; i >= 0; i--) {
            lmin[i] = a[i];
            if(i + 1 < n) {
                lmin[i] = min(lmin[i], lmin[i + 1]);
            }
        }

        int mx = 0;
        for(int i = 0; i < n; i++) {
            mx = max(mx, a[i]);
            if(i == n - 1 || mx <= lmin[i + 1]) {
                ans++;
            }
        }
        return ans;
    }
};
