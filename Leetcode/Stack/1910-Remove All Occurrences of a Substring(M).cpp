class Solution {
public:
    string removeOccurrences(string s, string t) {
        string ans = "";
        for(int i = 0; i < s.size(); i++) {
            ans += s[i];
            if(ans.size() >= t.size() && ans.substr(ans.size() - t.size(), t.size()) == t) {
                ans = ans.substr(0, ans.size() - t.size());
            }
        }
        return ans;
    }
};
