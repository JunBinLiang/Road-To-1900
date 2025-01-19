class Solution {
public:
    long long minMaxSubarraySum(vector<int>& a, int k) {
        long long ans = 0, s1 = 0, s2 = 0;
        vector<int> stk;
        int n = a.size();
        //As maximum
        vector<int> r(n, n), l(n, -1);
        for(int i = 0; i < n; i++) {
            while(stk.size() > 0 && a[i] > a[stk.back()]) {
                int j = stk.back();
                r[j] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        stk.clear();
        for(int i = n - 1; i >= 0; i--) {
            while(stk.size() > 0 && a[i] >= a[stk.back()]) {
                int j = stk.back();
                l[j] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        
        //cout << l[2] << " " << r[2] << endl;

        for(int i = 0; i < n; i++) {
            int lcnt = i - l[i], rcnt = r[i] - i;
            long long w = (lcnt) * (rcnt);
            
            int lp = i - k;
            int L = l[i] + 1, R = r[i] - 1;
            if(lp >= L) {
                w -= ((lp - L + 1ll) * (rcnt));
            } 
            
            
            lp = max(lp + 1, L);
            if(lp > i) continue;
            
            int rp1 = lp + k, rp2 = i + k;
            
            if(rp1 <= R) {
                if(rp2 <= R) {
                    int cnt = i - lp + 1;
                    int end = R - rp1 + 1;
                    int start = end - cnt + 1;
                    w -= ((end + 0ll + start) * cnt / 2);
                } else {
                    int end = R - rp1 + 1;
                    w -= ((end + 0ll + 1) * end / 2);
                }
            }
            
            s1 += (w * a[i]);
        }
        
        r = vector<int>(n, n);
        l = vector<int>(n, -1);
        stk.clear();
        
        for(int i = 0; i < n; i++) {
            while(stk.size() > 0 && a[i] < a[stk.back()]) {
                int j = stk.back();
                r[j] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        stk.clear();
        for(int i = n - 1; i >= 0; i--) {
            while(stk.size() > 0 && a[i] <= a[stk.back()]) {
                int j = stk.back();
                l[j] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
                
        for(int i = 0; i < n; i++) {
            int lcnt = i - l[i], rcnt = r[i] - i;
            long long w = (lcnt) * (rcnt);
            
            int lp = i - k;
            int L = l[i] + 1, R = r[i] - 1;
            if(lp >= L) {
                w -= ((lp - L + 1ll) * (rcnt));
            } 
            
            
            lp = max(lp + 1, L);
            if(lp > i) continue;
            
            int rp1 = lp + k, rp2 = i + k;
            
            if(rp1 <= R) {
                if(rp2 <= R) {
                    int cnt = i - lp + 1;
                    int end = R - rp1 + 1;
                    int start = end - cnt + 1;
                    w -= ((end + 0ll + start) * cnt / 2);
                } else {
                    int end = R - rp1 + 1;
                    w -= ((end + 0ll + 1) * end / 2);
                }
            }
            
            s1 += (w * a[i]);
        }
        
        
        return s1 + s2;
    }
};
