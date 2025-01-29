class Solution {
public:
    int minOperations(vector<int>& a) {
        int n = a.size(), flip = 0;
        for(int i = 0; i < n; i++) {
            if((a[i] + flip) % 2 == 0) {
                flip++;
            }
        }
        return flip;
    }
};
