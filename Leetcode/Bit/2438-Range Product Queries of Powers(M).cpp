class Solution {
public:
    const int MOD = 1e9 + 7;
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> a;
        for(int i = 0; i < 31; i++) {
            if(n & (1 << i)) {
                a.push_back(1 << i);
            }
        }

        vector<int> ans;
        for(auto& q : queries) {
            int l = q[0], r = q[1];
            long long p = 1;
            for(int i = l; i <= r; i++) {
                p *= a[i];
                p %= MOD;
            }
            ans.push_back(p);
        }
        return ans;
    }
};
