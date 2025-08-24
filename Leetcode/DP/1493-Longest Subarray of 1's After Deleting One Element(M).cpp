class Solution {
public:
    int longestSubarray(vector<int>& a) {
        int n = a.size();
        vector<int> R(n);
        int s = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] == 0) s = 0;
            else s++;
            R[i] = s;
        }

        int ans = 0;
        s = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] == 0) s = 0;
            else s++;
            if(i + 2 < n) ans = max(ans, s + R[i + 2]);
            ans = max(ans, min(s, n - 1));
        }
        return ans;
    }
};
