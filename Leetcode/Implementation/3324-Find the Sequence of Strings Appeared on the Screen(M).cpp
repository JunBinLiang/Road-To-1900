class Solution {
public:
    vector<string> stringSequence(string target) {
        vector<string> ans;
        string cur = "";
        for(int i = 0; i < target.size(); i++) {
            for(char c = 'a'; c <= target[i]; c++) {
                ans.push_back(cur + c);
            }
            cur += target[i];
        }
        return ans;
    }
};
