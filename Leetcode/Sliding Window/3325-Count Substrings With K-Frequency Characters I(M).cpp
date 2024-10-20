class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        long long ans = 0;
        vector<int> cnt(26);
        for(int i = 0, j = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']++;
            while(getMax(cnt) >= k) {
                ans += (s.size() - i);
                cnt[s[j++] - 'a']--;
            }
        }
        return ans;
    }
    
    int getMax(vector<int>& a) {
        int ans = a[0];
        for(int i = 0; i < 26; i++) {
            ans = max(ans, a[i]);
        }
        return ans;
    }
};
