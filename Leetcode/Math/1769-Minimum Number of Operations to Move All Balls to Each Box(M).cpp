class Solution {
public:
    vector<int> minOperations(string s) {
        vector<int> ans(s.size());
        for(int i = 0; i < s.size(); i++) {
            for(int j = 0; j < s.size(); j++) {
                if(s[j] == '1') {
                    ans[i] += abs(i - j);
                }
            }
        }
        return ans;
    }
};
