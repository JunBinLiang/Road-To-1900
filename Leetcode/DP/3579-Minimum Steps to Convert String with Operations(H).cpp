class Solution {
public:
    int minOperations(string s, string t) {
        int n = s.size();
        vector<vector<int>> w(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            string s1 = "", s2 = "";
            for(int j = i; j < n; j++) {
                s1 += s[j];
                s2 += t[j];
                string rev = s1;
                reverse(rev.begin(), rev.end());
                w[i][j] = min(cal(s1, s2), 1 + cal(rev, s2));
            }
        }

        vector<int> dp(n, 1e9);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= i; j++) {
                int cost = w[j][i];
                if(j > 0) cost += dp[j - 1];
                cout << j << " " << i << " " << cost << " " << endl;
                dp[i] = min(dp[i], cost);
            }
        }
        return dp.back();
    }

    int cal(string& s, string& t) {
        int n = s.size();
        vector<int> cnt1(26), cnt2(26);
        int ans = 0;
        map<pair<char, char>, int> mp;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] != t[i]) {
                pair<char, char> p = {t[i], s[i]};
                if(mp.find(p) != mp.end() && mp[p] > 0) {
                    ans++;
                    mp[p]--;
                } else {
                    mp[{s[i], t[i]}]++;
                }
            }
        }
        for(auto it = mp.begin(); it != mp.end(); it++) {
            ans += it -> second;
        }
        return ans;
    }
};
