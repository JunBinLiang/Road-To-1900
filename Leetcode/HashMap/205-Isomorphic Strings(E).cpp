class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> match(256, -1);
        vector<bool> vis(256);
        for(int i = 0; i < s.size(); i++) {
            if(match[s[i]] == -1) {
                if(vis[t[i]]) {
                    return false;
                }
                vis[t[i]] = true;
                match[s[i]] = t[i];
            } else {
                if(match[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};
