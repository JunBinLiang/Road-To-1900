const int MOD = 1e9 + 7;
class Solution {
public:
    int minAdjacentSwaps(vector<int>& a, int L, int R) {
        int n = a.size();
        for(int i = 0; i < n; i++) {
            if(a[i] < L) {
                a[i] = 0;
            } else if(a[i] > R) {
                a[i] = 2;
            } else {
                a[i] = 1;
            }
        }

        long long ans = 0;
        vector<int> vec(3);
        for(int i = 0; i < n; i++) {
            for(int j = a[i] + 1; j < vec.size(); j++) {
                ans += vec[j];
            }
            vec[a[i]]++;
        }

        return (ans % MOD);
    }
};
