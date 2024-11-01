class Solution {
public:
    double myPow(double x, long long n) {
        if(n < 0) {
            return 1.0 / myPow(x, -n);
        }
        
        double res = 1.0;
        double mul = x;
        for(int i = 0; i < 32; i++) {
            if(n & (1ll << i)) {
                res *= mul;
            }
            mul *= mul;
        }
        return res;
    }
};
