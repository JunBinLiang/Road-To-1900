class Solution {
public:
    int findMinMoves(vector<int>& a) {
        int n = a.size(), s = 0;
        for(int x : a) s += x;
        if(s % n != 0) {
            return -1;
        }
        int avg = s / n, tot = 0;
        int sum = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            int in1 = 0, in2 = 0, out1 = 0, out2 = 0;
            if(sum < tot) {
                out1 = tot - sum;
            } else {
                in1 = sum - tot;
            }
            tot += avg;
            sum += a[i];
            if(sum < tot) {
                in2 = tot - sum;
            } else {
                out2 = sum - tot;
            }
            ans = max(ans, max(max(in1, in2), out1 + out2));
        }
        return ans;
    }
};
