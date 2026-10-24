class Solution {
public:
    int maxFixedPoints(vector<int>& a) {
        /*
        int n = a.size();
        vector<int> dp(n, 0);
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int x1 = a[i], y1 = i - a[i]; //(value, how many need to delete)
            if(y1 < 0) continue;
            dp[i] = 1;
            for(int j = 0; j < i; j++) {
                int x2 = a[j], y2 = j - a[j];
                if(y2 < 0) continue;
                if(x1 > x2 && y2 <= y1) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }

        for(int x : dp) ans = max(ans, x);
        return ans;
        */
        int n = a.size();
        vector<pair<int, int>> b;
        for(int i = 0; i < n; i++) {
            int x = a[i], y = i - a[i]; //(value, how many need to delete)
            if(y < 0) continue;
            b.push_back({y, x});
        }

        sort(b.begin(), b.end());
        vector<int> dp(n + 1, 1000000);
        dp[0] = -1;
        int ans = 0;
        for(int i = 0; i < b.size(); i++) {
            int x = b[i].second;
            int index = find(dp, x);
            if(x < dp[index]) {
                dp[index] = x;
            }
            ans = max(ans, index);
        }
        return ans;
    }

    int find(vector<int>& dp, int val) {
        int l = 0, r = dp.size() - 1;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(val > dp[mid]) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans + 1;
    }

};
