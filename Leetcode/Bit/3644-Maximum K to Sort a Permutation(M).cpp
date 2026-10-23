class Solution {
public:
    int sortPermutation(vector<int>& a) {
        if(isSorted(a)) {
            return 0;
        }
        int ans = (1 << 20) - 1;
        for(int i = 0; i < a.size(); i++) {
            if(a[i] != i) {
                ans &= a[i];
            }
        }
        return ans;
    }

    bool isSorted(vector<int>& a) {
        for(int i = 0; i < a.size() - 1; i++) {
            if(a[i] > a[i + 1]) {
                return false;
            }
        }
        return true;
    }
};
