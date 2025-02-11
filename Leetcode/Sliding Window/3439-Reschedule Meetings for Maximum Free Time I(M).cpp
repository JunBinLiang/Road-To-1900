class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<pair<int, int>> a;
        int n = startTime.size();
        for(int i = 0; i < n; i++) {
            a.push_back({startTime[i], endTime[i]});
        }
        
        int ans = 0;
        int s = 0;
        for(int i = 0; i < n; i++) {
            s += (a[i].second - a[i].first);
            if(i + 1 >= k) {
                int l = 0;
                if(i - k >= 0) l = a[i - k].second;
                int r = eventTime;
                if(i + 1 < n) r = a[i + 1].first;
                ans = max(ans, (r - l) - s);
                s -= (a[i - k + 1].second - a[i - k + 1].first);
            }
        }
        return ans;
    }
};
