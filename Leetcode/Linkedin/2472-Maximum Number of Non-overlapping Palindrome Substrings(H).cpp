class Solution {
public:
    int maxPalindromes(string s, int k) {
        
        vector<int> dp(s.size());
        vector<vector<bool>> p(s.size(), vector<bool>(s.size()));
        for(int i = 0; i < s.size(); i++) {
            int l = i, r = i;
            while(l >= 0 && r < s.size()) {
                if(s[l] != s[r]) break;
                p[l][r] = true;
                l--; r++;
            }
        }
        
        for(int i = 0; i < s.size(); i++) {
            int l = i, r = i + 1;
            while(l >= 0 && r < s.size()) {
                if(s[l] != s[r]) break;
                p[l][r] = true;
                l--; r++;
            }
        }
        
        for(int i = 0; i < s.size(); i++) {
            for(int j = i; j >= 0; j--) {
                if(i - j + 1 >= k && p[j][i]) {
                    if(j == 0) dp[i] = max(dp[i], 1);
                    else dp[i] = max(dp[i], 1 + dp[j - 1]);
                }
            }
            if(i) dp[i] = max(dp[i], dp[i - 1]);
        }
        return dp.back();
    }
    
    bool isp(string& s, int l, int r) {
        while(l <= r){
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }
};
