class Solution {
public:
    int minimizedMaximum(int n, vector<int>& a) {
        sort(a.begin(), a.end());
        int l = 1, r = a.back();
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int cnt = 0;
            for(int x : a) {
                cnt += (x / mid);
                if(x % mid) cnt++;
            }
            if(cnt <= n) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
