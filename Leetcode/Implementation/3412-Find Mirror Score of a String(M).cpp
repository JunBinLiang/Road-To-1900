class Solution {
public:
    long long calculateScore(string s) {
        long long ans = 0;
        vector<vector<int>> p(26);
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            int rc = 26 - c - 1;
            if(p[rc].size()) {
                int j = p[rc].back(); p[rc].pop_back();
                ans += (i - j);
            } else {
                p[c].push_back(i);
            }
        }
        return ans;
    }
};
