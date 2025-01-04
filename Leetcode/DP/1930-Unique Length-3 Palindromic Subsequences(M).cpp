class Solution {
public:
    int countPalindromicSubsequence(string s) {
        unordered_set<string> ans;
        vector<bool> vis(26);
        unordered_map<char, set<char>> mp;
        for(int i = 0; i < s.size(); i++) {
            for(auto c : mp[s[i]]) {
                string t = "";
                t += s[i];
                t += c;
                t += s[i];
                ans.insert(t);
            }
            for(int j = 0; j < 26; j++) {
                if(vis[j]) {
                    char c = (char)(j + 'a');
                    mp[c].insert(s[i]);
                }
            }
            vis[s[i] - 'a'] = true;
        }
        return ans.size();
    }
};
