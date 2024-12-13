class Solution {
public:
    long long findScore(vector<int>& nums) {
        long long ans = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<bool> vis(nums.size());
        for(int i = 0; i < nums.size(); i++) {
            pq.push({nums[i], i});
        }
        
        while(pq.size() > 0) {
            pair<int, int> p = pq.top(); pq.pop();
            if(vis[p.second]) {
                continue;
            }
            ans += p.first;
            if(p.second > 0) {
                vis[p.second - 1] = true;
            }
            if(p.second + 1 < nums.size()) {
                vis[p.second + 1] = true;
            }
        }
        
        return ans;
    }
};
