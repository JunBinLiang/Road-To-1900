class Solution {
public:
    string lexSmallestAfterDeletion(string s) {
        int n = s.size();
        vector<int> cnt(26);
        for(char c : s) {
            cnt[c - 'a']++;
        }

        vector<char> stk;
        for(char c : s) {
            while(stk.size() > 0 && c < stk.back()) {
                char last = stk.back();
                if(cnt[last - 'a'] > 1) {
                    stk.pop_back();
                    cnt[last - 'a']--;
                } else {
                    break;
                }
            }
            stk.push_back(c);
        }

        while(stk.size() > 0 && cnt[stk.back() - 'a'] > 1) {
            char last = stk.back();
            cnt[last - 'a']--;
            stk.pop_back();
        }

        string ans = "";
        for(char c : stk) ans += c;
        return ans;
        
    }
};
