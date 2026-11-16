long long dp[62][2][62];

class Solution {
public:
    long long popcountDepth(long n, int k) {
        if(k == 0) {
            return 1;
        }

        k++; //use the sequence length for convinience

        //brute for for small number 
        vector<int> dep(61, 1);
        for(int i = 1; i <= 60; i++) {
            int x = i;
            while(x != 1) {
                dep[i]++;
                x = bitcount(x);
            }
        }

        long long ans = 0;
        for(int i = 1; i <= 60; i++) {
            if(dep[i] == k - 1) {
                memset(dp, -1, sizeof dp);
                long long cnt = dfs(n, 60, 1, i);
                if(i == 1) cnt--; //remove 1
                ans += cnt;
            }
        }
        return ans;
    }

    long long dfs(long long n, int i, int same, int t) {
        if(i < 0) {
            if(t == 0) {
                return 1;
            }
            return 0;
        }

        if(dp[i][same][t] != -1) {
            return dp[i][same][t];
        }

        long long ans = 0;
        int bit = 0;
        if(n & (1ll << i)) bit = 1;
        if(same == 1) { //same
            if(bit == 1) {
                if(t > 0) {
                    ans += dfs(n, i - 1, 1, t - 1); // 1
                }
                ans += dfs(n, i - 1, 0, t); // 0
            } else {
                ans += dfs(n, i - 1, same, t);
            }
        } else {
            if(t > 0) {
                ans += dfs(n, i - 1, 0, t - 1); // 1
            }
            ans += dfs(n, i - 1, 0, t); // 0
        }
        return dp[i][same][t] = ans;
    }

    int bitcount(long long x) {
        int cnt = 0;
        for(int i = 0; i < 60; i++) {
            if(x & (1ll << i)) {
                cnt++;
            }
        }
        return cnt;
    }
};
