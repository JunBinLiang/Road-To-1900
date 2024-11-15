class Solution {
public:
    long long maxRunTime(int n, vector<int>& a) {
        sort(a.begin(), a.end());
        long long l = 0, r = 1e14;
        long long ans = -1;
        while(l <= r) {
            long long mid = l + (r - l) / 2;
            //We need n battery to be turn on at least during mid minutes
            long long s = 0;
            for(int x : a) {
                s += min((x + 0ll), mid);
            }
            
            if(s >= (mid * n)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
