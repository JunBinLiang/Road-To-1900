class Solution {
public:
    long long findScore(vector<int>& a) {
        long long ans = 0;
        set<pair<int, int>> s;
        int n = a.size();
        for(int i = 0; i < n; i++) {
            s.insert({a[i], i});
        }
        while(s.size() > 0) {
            auto it = s.begin();
            int i = it -> second;
            ans += a[i];
            s.erase(it);
            if(i + 1 < n) {
                s.erase({a[i + 1], i + 1});
            } 
            if(i) {
                s.erase({a[i - 1], i - 1});
            }
        }
        return ans; 
    }
};
