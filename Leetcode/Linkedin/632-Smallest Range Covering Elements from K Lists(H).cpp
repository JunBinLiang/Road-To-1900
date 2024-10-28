class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& a) {
        int n = a.size();
        vector<pair<int, int>> b;
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < a[i].size(); j++) {
                b.push_back({a[i][j], i});
            }
        }
        sort(b.begin(), b.end());
        unordered_map<int, int> mp;
        vector<int> ans = {-1, -1};
        for(int i = 0, j = 0; i < b.size(); i++) {
            mp[b[i].second]++;
            while(mp.size() == n) {
                int L = b[j].first, R = b[i].first;
                update(ans, L, R);
                mp[b[j].second]--;
                if(mp[b[j].second] == 0) {
                    mp.erase(b[j].second);
                }
                j++;
            }
        }
        return ans;
    }
    
    void update(vector<int>& ans, int L, int R) {
        if(ans[0] == -1) {
            ans = {L, R};
        } else {
            if(R - L + 1 < ans[1] - ans[0] + 1) {
                ans = {L, R};
            }
        }
    }
};
