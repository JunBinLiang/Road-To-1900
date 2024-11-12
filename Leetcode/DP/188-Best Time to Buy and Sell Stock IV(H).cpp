class Solution {
public:
    int maxProfit(int k, vector<int>& a) {
        int n = a.size();
        
        vector<int> pdp(k + 1, -1000000);
        vector<int> cdp(k + 1, 0);
        pdp[0] = (-a[0]);
        
        
        //cdp[j] : 到第i天，操作j次最多赚多少
        for(int i = 1; i < n; i++) { 
            for(int j = 1; j <= min(i, k); j++) {
                int best = a[i] + pdp[j - 1];
                cdp[j] = max(cdp[j], best);
            }
            
            pdp[0] = max(pdp[0], -a[i]);
            if(i + 1 < n) {
                for(int j = 1; j <= min(i, k); j++) {
                    pdp[j] = max(pdp[j], cdp[j] - a[i + 1]);
                }
            }
        }
        
        int ans = 0;
        for(int i = 0; i < cdp.size(); i++) {
            ans = max(ans, cdp[i]);
        }
        
        return ans;
    }
};
