class Solution {
public:
    map<int, int> win, sums;
    int maxSubarray(vector<int>& a) {
        int n = a.size(), ans = 0;
        for(int l = 0, r = 0; r < n; r++) {
            win[a[r]]++;
            for(int i = l; i < r; i++) {
                sums[a[i] + a[r]]++;
            }
            while(l <= r && bad()) {
                for(int i = l + 1; i <= r; i++) {
                    sums[a[l] + a[i]]--;
                }
                win[a[l]]--;
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }

    bool bad() {
        for(auto it = sums.begin(); it != sums.end(); it++) {
            if((it -> second) == 0) continue;
            if(win[it -> first]) {
                return true;
            }
        }
        return false;
    }
};
