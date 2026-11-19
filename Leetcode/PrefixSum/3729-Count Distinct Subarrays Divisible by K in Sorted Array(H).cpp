class Solution {
public:
    long long numGoodSubarrays(vector<int>& a, int k) {
        int n = a.size();
        long long s = 0, ans = 0;
        map<int, long long> mp;
        for(int i = 0; i < n; i++) {
            int j = i;
            vector<long long> b;
            while(j < n && a[j] == a[i]) {
                s += a[j];
                b.push_back(s);
                if(s % k == 0) {
                    ans++;
                }
                ans += mp[s % k];
                j++;
            }
            i = j - 1;
            for(long long x : b) {
                mp[x % k]++;
            }
        }
        return ans;
    }
};
