class Solution {
public:
    long long dividePlayers(vector<int>& a) {
        sort(a.begin(), a.end());
        long long ans = 0;
        int s = a[0] + a.back();
        int l = 0, r = a.size() - 1;
        while(l < r) {
            if(a[l] + a[r] != s) return -1;
            ans += (a[l++] * a[r--]);
        }
        return ans;
    }
};
