class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& a, vector<int>& p) {
        vector<vector<int>> ans;
        if(a.size() == 0) {
            ans.push_back(p);
            return ans;
        }
        
        if(p[1] < a[0][0]) {
            ans.push_back(p);
        }
        
        for(int i = 0; i < a.size(); i++) {
            if(a[i][1] >= p[0] && a[i][0] <= p[1]) { //intersect
                int j = i;
                int L = min(a[i][0], p[0]), R = max(a[i][1], p[1]);
                while(j < a.size() && a[j][0] <= R) {
                    L = min(L, a[j][0]);
                    R = max(R, a[j][1]);
                    j++;
                }
                ans.push_back({L, R});
                i = j - 1;
            } else if(i + 1 < a.size() && p[0] > a[i][1] && p[1] < a[i + 1][0]) {
                ans.push_back(a[i]);
                ans.push_back(p);
            } else {
                ans.push_back(a[i]);
            }
        }
        
        if(p[0] > a.back()[1]) {
            ans.push_back(p);
        }
        
        return ans;
    }
};
