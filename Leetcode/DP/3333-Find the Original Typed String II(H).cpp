const int MOD = 1e9 + 7;
class Solution {
public:
    int possibleStringCount(string s, int k) {
        vector<int> a;
        for(int i = 0; i < s.size(); i++) {
            int j = i;
            int cnt = 0;
            while(j < s.size() && s[i] == s[j]) {
                cnt++;
                j++;
            }
            a.push_back(cnt);
            i = j - 1;
        }
        
        long long tot = 1;
        for(int i = 0; i < a.size(); i++) {
            tot *= a[i];
            tot %= MOD;
        }
        //at most k - 1
        return (tot - cal(a, k - 1) + MOD) % MOD;
    }
    
    long long get(vector<long long>& p, int l, int r) {
        if(l == 0) return p[r];
        return (p[r] - p[l - 1] + MOD) % MOD;
    }
    
    long long cal(vector<int>& a, int k) {
        if(a.size() > k) {
            return 0;
        }
        
        vector<long long> dp(k + 1);
        dp[0] = 1;
        vector<long long> p(k + 1); //prefix sum
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < dp.size(); j++) {
                p[j] = dp[j];
                if(j) {
                    p[j] += p[j - 1];
                    p[j] %= MOD;
                }
            }
            
            vector<long long> cur(k + 1);
            for(int j = 1; j <= k; j++) {
                cur[j] = get(p, max(0, j - a[i]), j - 1);
            }
            dp = cur;
        }
        long long ans = 0;
        for(int i = 0; i < dp.size(); i++) {
            ans += dp[i];
            ans %= MOD;
        }
        return ans;
    }
};



const int MOD = 1e9 + 7;
class Solution {
public:
    int possibleStringCount(string s, int k) {
        int n = s.size();
        vector<int> a;
        for(int i = 0; i < n; i++) {
            int j = i;
            while(j < n && s[j] == s[i]) {
                j++;
            }
            a.push_back(j - i);
            i = j - 1;
        }

        long long tot = 1;
        for(int i = 0; i < a.size(); i++) {
            tot *= a[i];
            tot %= MOD;
        }
        if(k <= a.size()) {
            return tot;
        }

        vector<vector<long long>> dp(a.size(), vector<long long>(k, 0));
        for(int i = 0; i < a.size(); i++) {
            int cnt = a[i] - 1;
            if(i == 0) {
                for(int j = a.size(); j <= min(k - 1, (int)(cnt + a.size())); j++) {
                    dp[i][j] = 1;
                }

                for(int j = 1; j <= k - 1; j++) {
                    dp[i][j] += dp[i][j - 1];
                    dp[i][j] %= MOD;
                }
                continue;
            }

            for(int j = a.size(); j <= k - 1; j++) {
                if(j <= cnt) {
                    dp[i][j] += dp[i - 1][j];
                } else {
                    dp[i][j] += ((dp[i - 1][j] - dp[i - 1][j - cnt - 1] + MOD) % MOD);
                }
            }

            for(int j = 1; j <= k - 1; j++) {
                dp[i][j] += dp[i][j - 1];
                dp[i][j] %= MOD;
            }
        }
        
        return (tot - dp.back()[k - 1] + MOD) % MOD;   
    }
};
