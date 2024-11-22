class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int ans = 0;
        unordered_map<string, int> mp;
        for(int i = 0; i < n; i++) {
            string temp = "";
            for(int j = 0; j < m; j++) {
                if(j == 0) {
                    temp += "0"; //no flip
                } else {
                    if(a[i][j] == a[i][0]) temp += "0";
                    else temp += "1";
                }
            }
            mp[temp]++;
            ans = max(ans, mp[temp]);
        }
        return ans;
    }
};
