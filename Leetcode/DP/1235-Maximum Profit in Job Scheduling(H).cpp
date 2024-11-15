class Solution {
public:
    int jobScheduling(vector<int>& s, vector<int>& e, vector<int>& profit) {
        int n = s.size();
        vector<vector<int>> a;
        for(int i = 0; i < n; i++) {
            a.push_back({s[i], e[i], profit[i]});
        }
        
        int ans = 0;
        sort(a.begin(), a.end());
        priority_queue<pair<int, int>> pq;
        int best = 0;
        for(int i = 0; i < a.size(); i++) {
            int l = a[i][0], r = a[i][1], w = a[i][2];
            while(pq.size() > 0 && abs(pq.top().first) <= l) {
                pair<int, int> p = pq.top(); pq.pop();
                best = max(best, p.second);
            }
            ans = max(ans, w + best);
            pq.push({-r, w + best});
        }
        return ans;
    }
};
