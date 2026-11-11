const int MOD = 1e9 + 7;
class Solution {
public:
    int alternatingXOR(vector<int>& a, int t1, int t2) {
        int n = a.size();
        int pxo = 0;
        long long ans = 0;
        map<int, long long> dp1, dp2;
        for(int i = 0; i < n; i++) {
            pxo ^= a[i];
            int com1 = pxo ^ t1;
            int com2 = pxo ^ t2;
            int add1 = 0;
            int add2 = 0;
            
            if(dp2.find(com1) != dp2.end()) {
                add1 = dp2[com1];
            }

            if(dp1.find(com2) != dp1.end()) {
                add2 = dp1[com2];
            }

            dp1[pxo] += add1;
            dp1[pxo] %= MOD;
            dp2[pxo] += add2;
            dp2[pxo] %= MOD;
            if(i == n - 1) {
                ans += add1;
                ans += add2;
            } 

            if(pxo == t1) {
                dp1[pxo]++;
                dp1[pxo] %= MOD;
                if(i == n - 1) ans++;
            }
        }
        ans %= MOD;
        return ans;
    }
};
