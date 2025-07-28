int base[30];
class Solution {
public:
    long long maximizeXorAndXor(vector<int>& a) {
        int n = a.size();

        long long ans = 0;
        for(int st = 0; st < (1 << n); st++) {
            vector<int> b;
            int an = -1;
            int s = 0;
            for(int j = 0; j < n; j++) {
                if(st & (1 << j)) {
                    if(an == -1) an = a[j];
                    else an &= a[j];
                } else {
                    b.push_back(a[j]);
                    s ^= a[j];
                }
            }

            int rs = 0;
            for(int j = 0; j < 30; j++) {
                if(s & (1 << j)) {

                } else {
                    rs += (1 << j);
                }
            }

            //linear basic
            memset(base, 0, sizeof base);
            for(int& x : b) {
                insert(x & rs);
            }
            int xo = 0;
            for(int j = 29; j >= 0; j--) {
                if((xo ^ base[j]) > xo) {
                    xo ^= base[j];
                }
            }
            ans = max(ans, an + 0ll + s + 2 * xo);
        }
        return ans;
    }

    void insert(int x) {
        for(int i = 29; i >= 0; i--) {
            if(x & (1 << i)) {
                if(base[i]) x ^= base[i];
                else {
                    base[i] = x;
                    return;
                }
            }
        }
    }
};
