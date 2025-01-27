class Solution {
public:
    long long minCost(vector<int>& a, vector<int>& b, long long k) {
        long long ans = 0;
        for(int i = 0; i < a.size(); i++) {
            ans += abs(a[i] - b[i]);
        }
        
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        long long s = 0;
        for(int i = 0; i < a.size(); i++) {
            s += abs(a[i] - b[i]);
        }
        return min(ans, s + k);
    }
};
