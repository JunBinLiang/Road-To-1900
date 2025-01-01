class Solution {
public:
    int maxScore(string s) {
        int ans = 0;
        for(int i = 0; i < s.size() - 1; i++) {
            int one = 0, zero = 0;
            for(int j = 0; j <= i; j++) {
                zero += (s[j] == '0');
            }
            for(int j = i + 1; j < s.size(); j++) {
                one += (s[j] == '1');
            }
            ans = max(ans, one + zero);
        }
        return ans;
    }
};
