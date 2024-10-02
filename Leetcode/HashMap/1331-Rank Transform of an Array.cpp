class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& a) {
        vector<int> b(a.begin(), a.end());
        sort(b.begin(), b.end());
        map<int, int> rk;
        int id = 1;
        for(int i = 0; i < b.size(); i++) {
            if(rk.find(b[i]) == rk.end()) {
                rk[b[i]] = id++;
            }
        }
        
        vector<int> ans;
        for(int i = 0; i < a.size(); i++) {
            ans.push_back(rk[a[i]]);
        }
        return ans;
    }
};
