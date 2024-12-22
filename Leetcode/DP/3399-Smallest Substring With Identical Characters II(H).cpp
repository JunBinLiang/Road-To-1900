const int N = 1e5 + 10;
int p0[N], p1[N];
int dp[N][2];

class Solution {
public:
    int minLength(string s, int k) {        
        int n = s.size();
        int sum1 = 0, sum2 = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') sum1++;
            else sum2++;
            p0[i] = sum1;
            p1[i] = sum2;
            dp[i][0] = dp[i][1] = 1e6;
        }
        int l = 1, r = n, ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(s, mid, k)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }        
        return ans;
    }
    
    bool ok(string& s, int k, int ops) {
        int n = s.size();
        if(s[0] == '0') {
            dp[0][0] = 0;
            dp[0][1] = 1;
        } else {
            dp[0][0] = 1;
            dp[0][1] = 0;
        }
        
        deque<pair<int, int>> pq0, pq1;
        pq0.push_back({dp[0][0] - p0[0], 0});
        pq1.push_back({dp[0][1] - p1[0], 0});
        for(int i = 1; i < n; i++) {
            while(pq0.size() > 0 && i - pq0.front().second > k) pq0.pop_front();
            while(pq1.size() > 0 && i - pq1.front().second > k) pq1.pop_front();
            dp[i][0] = pq1.front().first + p1[i];
            dp[i][1] = pq0.front().first + p0[i];
            
            if(i + 1 <= k) {
                dp[i][0] = min(dp[i][0], p1[i]);
                dp[i][1] = min(dp[i][1], p0[i]);
            }
            while(pq0.size() > 0 && dp[i][0] - p0[i] < pq0.back().first) pq0.pop_back();
            while(pq1.size() > 0 && dp[i][1] - p1[i] < pq1.back().first) pq1.pop_back();
            pq0.push_back({dp[i][0] - p0[i], i});
            pq1.push_back({dp[i][1] - p1[i], i});
        }
        return min(dp[n - 1][0], dp[n - 1][1]) <= ops;
    }
};
