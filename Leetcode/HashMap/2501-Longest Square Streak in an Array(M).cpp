class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        set<long long> s;
        for(int x : nums) s.insert(x);
        int ans = 0;
        for(long long x : nums) {
            int cnt = 0;
            while(s.find(x) != s.end()) {
                x = x * x;
                cnt++;
            }
            ans = max(ans, cnt);
        }
        return ans >= 2 ? ans : -1;
    }
};
