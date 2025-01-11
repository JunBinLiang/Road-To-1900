class Solution {
public:
    bool canConstruct(string s, int k) {
        if(k > s.size()) {
            return false;
        }
        
        vector<int> cnt(26);
        for(char c : s) {
            cnt[c - 'a']++;
        }
        
        int odd = 0;
        for(int i = 0; i < 26; i++) {
            if(cnt[i] % 2 == 1) {
                odd++;
            }
        }
        
        if(odd > k) {
            return false;
        }
        
        int remain = k - odd;
        return (s.size() - odd) >= remain;
    }
};
