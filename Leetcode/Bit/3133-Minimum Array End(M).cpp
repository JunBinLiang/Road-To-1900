class Solution {
public:
    long long minEnd(int n, int x) {
        n--;
        vector<int> a;
        for(int i = 0; i < 30; i++) {
            if(n & (1 << i)) {
                a.push_back(1);
            } else {
                a.push_back(0);
            }
        }
        
        int j = 0;
        long long ans = x;
        for(int i = 0; i < 60 && j < a.size(); i++) {
            if(x & (1ll << i)) continue;
            ans |= ((a[j++] + 0ll) << i);
        }
        return ans;
    }
};
