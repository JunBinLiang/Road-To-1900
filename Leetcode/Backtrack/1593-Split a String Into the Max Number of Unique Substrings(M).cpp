class Solution {
public:
    int ans = 0;
    int maxUniqueSplit(string s) {
        vector<string> cur;
        dfs(s, 0, cur);
        return ans;
    }
    
    void dfs(string& s, int index, vector<string>& cur) {
        if(index >= s.size()) {
            set<string> uni(cur.begin(), cur.end());
            ans = max(ans, (int)(uni.size()));
            return;
        }
        
        string temp = "";
        for(int i = index; i < s.size(); i++) {
            temp += s[i];
            cur.push_back(temp);
            dfs(s, i + 1, cur);
            cur.pop_back();
        }
    }
};
