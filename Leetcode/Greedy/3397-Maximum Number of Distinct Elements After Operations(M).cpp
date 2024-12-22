class Solution {
public:
    int maxDistinctElements(vector<int>& a, int k) {
        vector<pair<int, int>> b;
        for(int i = 0; i < a.size(); i++) {
            b.push_back({a[i] - k, a[i] + k});
        }
        sort(b.begin(), b.end());
        
        int p = -2e9 + 10, ans = 0;
        for(auto& [l, r] : b) {
            if(p < l) {
                p = l;
                ans++;
            } else if(p + 1 <= r) {
                p++;
                ans++;
            }
        }
        return ans;
    }
};
