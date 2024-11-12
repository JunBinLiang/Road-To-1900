class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& a, vector<int>& q) {
        sort(a.begin(), a.end());
        for(int i = 1; i < a.size(); i++) {
            a[i][1] = max(a[i][1], a[i - 1][1]);
        }
        
        vector<int> ans(q.size());
        for(int i = 0; i < q.size(); i++) {
            int l = 0, r = a.size() - 1;
            int p = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[mid][0] <= q[i]) {
                    p = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if(p != -1) ans[i] = a[p][1];
        }
        return ans;
    }
};
