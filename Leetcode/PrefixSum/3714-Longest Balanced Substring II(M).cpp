class Solution {
public:
    int longestBalanced(string s) {
        int ans = 0;
        map<pair<int, int>, int> mp;
        vector<int> cnt(3);
        for(int i = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']++;
            if(cnt[0] == cnt[1] && cnt[1] == cnt[2]) ans = max(ans, i + 1);
            int dif1 = cnt[1] - cnt[0];
            int dif2 = cnt[2] - cnt[1];
            if(mp.find({dif1, dif2}) == mp.end()) mp[{dif1, dif2}] = i;
            else ans = max(ans, i - mp[{dif1, dif2}]);
        }
        
        for(int i = 0; i < s.size(); i++) { // single
            int j = i;
            int cnt = 0;
            while(j < s.size() && s[j] == s[i]) {
                j++;
                cnt++;
            }
            i = j - 1;
            ans = max(ans, cnt);
        }

        ans = max(ans, find1(s, 'a', 'b'));
        ans = max(ans, find1(s, 'a', 'c'));
        ans = max(ans, find1(s, 'b', 'c'));

        return ans;
    }

    
    int find1(string s, char c1, char c2) {
        int ans = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] != c1 && s[i] != c2) continue;
            int j = i;
            int psum = 0;
            map<int, int> mp;
            while(j < s.size() && (s[j] == c1 || s[j] == c2)) {
                if(s[j] == c1) psum++;
                else psum--;
                if(psum == 0) {
                    ans = max(ans, j - i + 1);
                }

                if(mp.find(psum) == mp.end()) {
                    mp[psum] = j;
                } else {
                    ans = max(ans, j - mp[psum]);
                }
                j++;
            }
            i = j - 1;
        }
        return ans;
    } 
};
