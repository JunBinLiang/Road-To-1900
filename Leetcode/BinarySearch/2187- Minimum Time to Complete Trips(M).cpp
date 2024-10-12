class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long l = 1, r = 10000000000000000ll;
        long long ans = -1;
        while(l <= r) {
            long long mid = l + (r - l) / 2;
            long long s = 0;
            for(int t : time) {
                s += mid / t;
                if(s >= totalTrips) break;
            }
            if(s >= totalTrips) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
