class Solution {
public:
    long long maximumSubarraySum(vector<int>& a, int k) {
        long long ans = 0, s = 0;
        unordered_map<int, int> mp;
        for(int i = 0; i < a.size(); i++) {
            mp[a[i]]++;
            s += a[i];
            if(i + 1 >= k) {
                if(mp.size() == k) {
                    ans = max(ans, s);
                }
                s -= a[i - k + 1];
                mp[a[i - k + 1]]--;
                if(mp[a[i - k + 1]] == 0) {
                    mp.erase(a[i - k + 1]);
                }
            }
        }
        return ans;
    }
};
