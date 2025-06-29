class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& a) {
        int n = a.size();
        map<int, int> mp;
        vector<int> dp(n);
        for(int i = 1; i < n; i++) {
            int c = com(a[i], a[i - 1]);
            mp[c]++;
            dp[i] = c;
        }

        vector<int> ans;
        for(int i = 0; i < n; i++) {
            if(i + 1 < n) {
                del(mp, dp[i + 1]);
            }

            if(i > 0) {
                del(mp, dp[i]);
            }

            int mx = 0;
            if(mp.size() > 0) {
                auto it = mp.end(); 
                it--;
                mx = max(mx, it -> first);
            }

            if(i > 0 && i + 1 < n) {
                int c = com(a[i - 1], a[i + 1]);
                mx = max(mx, c);
            }
            
            ans.push_back(mx);

            if(i + 1 < n) {
                mp[dp[i + 1]]++;
            }

            if(i > 0) {
                mp[dp[i]]++;
            }
        }
        return ans;
    }

    void del(map<int, int>& mp, int k) {
        mp[k]--;
        if(mp[k] == 0) mp.erase(k);
    }

    int com(string& s, string& t) {
        int n = s.size(), m = t.size();
        int ans = 0;
        for(int i = 0; i < min(m, n); i++) {
            if(s[i] != t[i]) break;
            ans++;
        }
        return ans;
    }
};
