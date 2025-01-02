class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        vector<int> p(words.size());
        for(int i = 0; i < words.size(); i++) {
            string& s = words[i];
            if(isv(s[0]) && isv(s.back())) {
                p[i] = 1;
            }
            if(i) {
                p[i] += p[i - 1];
            }
        }
        
        vector<int> ans;
        for(auto& vec : queries) {
            int l = vec[0], r = vec[1];
            ans.push_back(p[r] - (l == 0 ? 0 : p[l - 1]));
        }
        return ans;
    }
    
    bool isv(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
