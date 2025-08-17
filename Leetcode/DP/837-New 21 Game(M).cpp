class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if(k == 0) {
            return 1;
        }
        vector<double> dp(n + 1);
        dp[0] = 1;
        double s = 1;
        double p = (1.0) / maxPts;
        for(int i = 1, j = 0; i <= n; i++) {
            dp[i] = s * p;
            if(i < k) {
                s += dp[i];
            }
            if(i - j >= maxPts && j < k) {
                s -= dp[j];
                j++;
            }
        }

        double ans = 0;
        for(int i = k; i <= n; i++) {
            ans += dp[i];
        }
        return ans;
    }
};
