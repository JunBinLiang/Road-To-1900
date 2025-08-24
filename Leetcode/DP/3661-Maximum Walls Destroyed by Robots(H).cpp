int q(vector<int>& a, int L, int R) {
    int l = 0, r = a.size() - 1;
    int p1 = -1, p2 = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;  
        if(a[mid] >= L) {
            p1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if(p1 == -1 || a[p1] > R) return 0;
    l = p1, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] <= R) {
            p2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return p2 - p1 + 1;
}

class Solution {
public:
    int maxWalls(vector<int>& a, vector<int>& b, vector<int>& c) {
        int n = a.size();
        vector<pair<int, int>> A;
        for(int i = 0; i < n; i++) {
            A.push_back({a[i], b[i]});
        }
        sort(A.begin(), A.end());
        sort(c.begin(), c.end());

        if(n == 1) {
            return max(q(c, a[0] - b[0], a[0]), q(c, a[0], a[0] + b[0]));
        }

        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = q(c, A[0].first - A[0].second, A[0].first);
        dp[0][1] = q(c, A[0].first, min(A[0].first + A[0].second, A[1].first - 1));

        for(int i = 0; i < n; i++) {
            int cur = A[i].first, d = A[i].second;
        }

        for(int i = 1; i < n; i++) {
            int cur = A[i].first, d = A[i].second;
            int p = A[i - 1].first, pto = p + A[i - 1].second;
            int nxt = 2e9;
            if(i + 1 < n) nxt = A[i + 1].first - 1;
            dp[i][1] = q(c, cur, min(nxt, cur + d)) + max(dp[i - 1][0], dp[i - 1][1]);

            if(pto >= cur - d) { //overlap
                dp[i][0] = max(dp[i][0], dp[i - 1][1] - q(c, p, min(pto, cur - 1)) + q(c, p, cur));
            } else {
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + q(c, cur - d, cur));
            }
            dp[i][0] = max(dp[i][0], q(c, max(cur - d, p + 1), cur) + dp[i - 1][0]);
        }

        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
        }
        return ans;
    }
};
