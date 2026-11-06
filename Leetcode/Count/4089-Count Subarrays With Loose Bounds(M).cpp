class Solution {
public:
    long long countSubarrays(vector<int>& a, int L, int R) {
        int n = a.size();
        long long ans = 0;
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] < L || a[i] > R) {
                cnt = 0;
            } else {
                cnt++;
            }
            ans += cnt;
        }

        return ans;
    }
};
