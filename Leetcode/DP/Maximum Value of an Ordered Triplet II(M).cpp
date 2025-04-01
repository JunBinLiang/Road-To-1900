class Solution {
public:
    long long maximumTripletValue(vector<int>& a) {
        int n = a.size();
        long long ans = 0;
        
        vector<int> r(n);
        for(int i = n - 1; i >= 0; i--) {
            r[i] = a[i];
            if(i + 1 < n) r[i] = max(r[i], r[i + 1]);
        }
        
        int leftmx = a[0];
        for(int i = 1; i < n - 1; i++) {
            ans = max(ans, (leftmx - a[i] + 0ll) * r[i + 1]);
            leftmx = max(a[i], leftmx);
        }
        
        return ans;
    }
};
