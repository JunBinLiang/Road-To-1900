class Solution {
public:
    bool isArraySpecial(vector<int>& a) {
        for(int i = 0; i < a.size() - 1; i++) {
            if((a[i] + a[i + 1]) & 1) continue;
            return false;
        }
        return true;
    }
};
