class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end());
        int n = events.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1)); 
        vector<int> maxs(k + 1, -1);
        int j = 0;
        priority_queue<pair<int, int>> pq;
        for(int i = 0; i < n; i++) {
            int s = events[i][0], e = events[i][1], w = events[i][2];
            while(pq.size() > 0 && s > -pq.top().first) {
                pair<int, int> p = pq.top(); pq.pop();
                int index = p.second;
                for(int j = 0; j <= k; j++) {
                    maxs[j] = max(maxs[j], dp[index][j]);
                }
            }

            dp[i][1] = w;
            for(int j = 2; j <= k; j++) {
                if(maxs[j - 1] != -1) {
                    dp[i][j] = w + maxs[j - 1];
                }
            }
            pq.push({-e, i});
        }

        int ans = 0;
        for(int i = 0; i < dp.size(); i++) {
            for(int j = 0; j < dp[0].size(); j++) {
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};
