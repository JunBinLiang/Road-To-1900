class Solution {
public:
    int totalMoney(int n) {
        int ans = 0;
        int start = 1;
        for(int i = 0; i < n; i++) {
            int shift = i / 7;
            ans += (start + shift + i % 7);
        }
        return ans;
    }
};
