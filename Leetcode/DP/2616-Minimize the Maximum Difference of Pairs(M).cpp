class Solution {
public:
    int minimizeMax(vector<int>& a, int p) {
        sort(a.begin(), a.end());
        int l = 0, r = 2e9;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int cnt = get(a, mid);
            if(cnt >= p) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }

    int get(vector<int>& a, int mid) {
        vector<int> dp(a.size());
        dp[0] = 0;
        for(int i = 1; i < a.size(); i++) {
            dp[i] = dp[i - 1];
            if(a[i] - a[i - 1] <= mid) {
                if(i - 2 >= 0) dp[i] = max(dp[i], dp[i - 2] + 1);
                else dp[i] = max(dp[i], 1);
            } 
        }
        return dp.back();
    }
};
