class Solution {
public:
    int longestPalindrome(string s, string t) {
        int ans = 0;

        int n = s.size(), m = t.size();
        reverse(t.begin(), t.end());
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        vector<int> max1(n + 1), max2(m + 1);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(s[i - 1] == t[j - 1]) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - 1][j - 1]);
                }
            }
        }

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++) {
                max1[i] = max(max1[i], dp[i][j]);
            }
        }

        for(int j = 0; j <= m; j++) {
            for(int i = 0; i <= n; i++) {
                max2[j] = max(max2[j], dp[i][j]);
            }
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                int len = dp[i][j];
                ans = max(ans, len * 2);
            }
        }

        for(int i = 0; i < n; i++) {
            int l = i, r = i;
            int cnt = 1;
            while(l >= 0 && r < n && s[l] == s[r]) {
                ans = max(ans, cnt);
                if(l - 1 >= 0) {
                    ans = max(ans, cnt + max1[l] * 2);
                }
                cnt += 2;
                l--;
                r++;
            }
        }

        for(int i = 0; i < n - 1; i++) {
            int l = i, r = i + 1;
            int cnt = 2;
            while(l >= 0 && r < n && s[l] == s[r]) {
                ans = max(ans, cnt);
                if(l - 1 >= 0) {
                    ans = max(ans, cnt + max1[l] * 2);
                }
                cnt += 2;
                l--;
                r++;
            }
        }


        for(int i = 0; i < m; i++) {
            int l = i, r = i;
            int cnt = 1;
            while(l >= 0 && r < m && t[l] == t[r]) {
                ans = max(ans, cnt);
                if(l - 1 >= 0) {
                    ans = max(ans, cnt + max2[l] * 2);
                }
                cnt += 2;
                l--;
                r++;
            }
        }

        for(int i = 0; i < m - 1; i++) {
            int l = i, r = i + 1;
            int cnt = 2;
            while(l >= 0 && r < m && t[l] == t[r]) {
                ans = max(ans, cnt);
                if(l - 1 >= 0) {
                    ans = max(ans, cnt + max2[l] * 2);
                }
                cnt += 2;
                l--;
                r++;
            }
        }
        
        return ans;
    }
};
