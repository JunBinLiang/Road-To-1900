class Solution {
public:
    long long countBadPairs(vector<int>& a) {
        int n = a.size();
        long long ans = (n + 0ll) * (n - 1) / 2;
        unordered_map<int, int> mp;
        for(int i = 0; i < n; i++) {
            ans -= (mp[i - a[i]]++);
        }
        return ans;
    }
};
