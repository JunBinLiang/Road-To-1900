const int N = 5050;
long long dp[N][N][2];

void reset(int n) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = 1e9;
        }
    }
}

long long f(vector<int>& a, int k) {
    int n = a.size();
    reset(n);
    long long ans = 1e9;
    
    dp[0][0][0] = 0; //not take first one
    int W = 0;
    if(a[0] <= max(a[1], a.back())) {
        W = max(a[1], a.back()) + 1 - a[0];
    }
    for(int i = 1; i < n; i++) {
        int p1 = a[i - 1], p2 = a[(i + 1) % n];
        int w = 0;
        if(a[i] <= max(p1, p2)) {
            w = max(p1, p2) + 1 - a[i];
        }
        for(int j = 0; j <= k; j++) {
            // not take
            dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1]);
            if(j) {
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][0] + w);
            }
        }
    }
    ans = min(ans, dp[n - 1][k][0]);
    ans = min(ans, dp[n - 1][k][1]);

    //take the first one
    reset(n);
    dp[0][1][1] = W;
    for(int i = 1; i < n - 1; i++) {
        int p1 = a[i - 1], p2 = a[(i + 1) % n];
        int w = 0;
        if(a[i] <= max(p1, p2)) {
            w = max(p1, p2) + 1 - a[i];
        }
        for(int j = 0; j <= k; j++) {
            // not take
            dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1]);
            if(j) {
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 1][0] + w);
            }
        }
    }

    ans = min(ans, dp[n - 2][k][0]);
    ans = min(ans, dp[n - 2][k][1]);
    return ans;
}

class Solution {
public:
    int minOperations(vector<int>& a, int k) {
        int n = a.size();
        if(k > (n) / 2) {
            return -1;
        }

        if(k == 0) {
            return 0;
        }

        vector<int> b;
        b.push_back(a.back());
        for(int i = 0; i < n - 1; i++) {
            b.push_back(a[i]);
        }

        
        int ans = min(f(a, k), f(b, k));
        return ans;
    }

    long long dfs(vector<int>& a, int i, int k, int p) {
        if(i >= a.size() - 1) {
            if(k != 0) {
                return 1e9;
            }
            return 0;
        }
        if(dp[i][k][p] != -1) {
            return dp[i][k][p];
        }

        long long ans = 1e9;
        if(p == 1) { // taken
            ans = min(ans, dfs(a, i + 1, k, 0));
        } else {
            ans = min(ans, dfs(a, i + 1, k, 0)); //not take also
            //take 
            if(k > 0) {
                int p1 = a[i - 1], p2 = a[(i + 1) % a.size()];
                int cur = a[i], w = 0;
                if(cur <= max(p1, p2)) {
                    w = 1 + max(p1, p2) - cur;
                }
                ans = min(ans, w + dfs(a, i + 1, k - 1, 1));
            }
        }
        return dp[i][k][p] = ans;
    }
};
