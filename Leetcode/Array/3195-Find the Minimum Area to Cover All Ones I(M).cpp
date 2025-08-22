class Solution {
public:
    int minimumArea(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int l = -1, r = -1, u = -1, d = -1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j]) {
                    r = max(r, j);
                    if(l == -1) l = j;
                    else l = min(l, j);
                    d = max(d, i);
                    if(u == -1) u = i;
                    else u = min(u, i);
                }
            }
        }
        return (d - u + 1) * (r - l + 1);
    }
};
