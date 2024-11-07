class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<int, long long> mp;
        for(int i = 0; i < segments.size(); i++) {
            int l = segments[i][0], r = segments[i][1], w = segments[i][2];
            mp[l] += w;
            mp[r] -= w;
        }
        
        int last = -1;
        long long sum = 0;
        vector<vector<long long>> ans;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            if(last == -1) {
                last = it -> first;
            } else {
                if(sum > 0) {
                    ans.push_back({last, it -> first, sum});
                }
                last = it -> first;
            }
            sum += it -> second;
        }
        return ans;
    }
};
