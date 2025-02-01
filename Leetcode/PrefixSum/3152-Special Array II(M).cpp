class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& a, vector<vector<int>>& queries) {
        vector<int> p;
        int s = 0;
        for(int i = 0; i < a.size() - 1; i++) {
            if((a[i] + a[i + 1]) & 1) {
                s++;
            }
            p.push_back(s);
        }
        
        vector<bool> ans;
        for(auto& q : queries) {
            int l = q[0], r = q[1];
            if(l == r) {
                ans.push_back(true);
            } else {
                int sum = (l == 0 ? p[r - 1] : p[r - 1] - p[l - 1]);
                if(sum == r - l) ans.push_back(true);
                else ans.push_back(false);
            }
        }
        return ans;
    }
};
