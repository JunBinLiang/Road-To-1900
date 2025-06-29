class Solution {
public:
    vector<string> partitionString(string s) {
        set<string> se;
        vector<string> ans;
        string cur = "";
        for(int i = 0; i < s.size(); i++) {
            cur += s[i];
            if(se.find(cur) == se.end()) {
                ans.push_back(cur);
                se.insert(cur);
                cur = "";
            } else {
                
            }
        }
        return ans;
    }
};
