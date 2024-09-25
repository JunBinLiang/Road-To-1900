int c1[256], c2[256];
class Solution {
public:
    long long validSubstringCount(string s, string t) {
        long long ans = 0;
        memset(c1, 0, sizeof c1);
        memset(c2, 0, sizeof c2);
        for(char c : t) c2[c]++;
        
        int over = 0;
        for(int i = 0; i < 256; i++) {
            if(c2[i]) over++;
        }
        
        for(int i = 0, j = 0; i < s.size(); i++) {
            c1[s[i]]++;
            if(c1[s[i]] == c2[s[i]]) over--;
            while(j < s.size() && over == 0) {
                ans += (s.size() - i);
                c1[s[j]]--;
                if(c1[s[j]] + 1 == c2[s[j]]) over++;
                j++;
            }
        }
        return ans;
    }
};
