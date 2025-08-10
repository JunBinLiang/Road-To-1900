class Solution {
public:
    bool reorderedPowerOf2(int n) {
        vector<int> cnt(10);
        while(n) {
            cnt[n % 10]++;
            n /= 10;
        }
        for(int i = 0; i < 31; i++) {
            if(ok(cnt, 1 << i)) {
                return true;
            }
        } 
        return false;
    }
    
    bool ok(vector<int>& cnt, int n) {
        vector<int> c(10);
        while(n) {
            c[n % 10]++;
            n /= 10;
        }

        for(int i = 0; i < 10; i++) {
            if(c[i] != cnt[i]) {
                return false;
            }
        }

        return true;
    }
};
