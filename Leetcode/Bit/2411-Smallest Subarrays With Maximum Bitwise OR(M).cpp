class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& a) {
        int n = a.size();
        vector<int> ans(n, -1);
        vector<deque<int>> p(31);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 31; j++) {
                if(a[i] & (1 << j)) {
                    p[j].push_back(i);
                }
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 31; j++) {
                if(p[j].size() && p[j].front() < i) p[j].pop_front();
            }

            for(int j = 0; j < 31; j++) {
                if(p[j].size()) ans[i] = max(ans[i], p[j].front() - i + 1);
            }
            if(ans[i] == -1) {
                ans[i] = 1;
            }
        }

        return ans;
    }
};
