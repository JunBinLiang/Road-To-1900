class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        vector<int> cnt(30);
        for(int x : candidates) {
            for(int i = 0; i < 30; i++) {
                if(x & (1 << i)) {
                    cnt[i]++;
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < cnt.size(); i++) {
            ans = max(ans, cnt[i]);
        }
        return ans;
    }
};
