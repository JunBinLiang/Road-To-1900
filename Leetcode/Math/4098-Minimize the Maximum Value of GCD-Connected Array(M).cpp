class Solution {
public:
    long long minimumMaxValue(int n, int index, int value) {
        int mn = value;
        for(int i = 2; i * i <= value; i++) {
            if(value % i == 0) {
                mn = i;
                break;
            }
        }

        if(index == 0 && value == 1) {
            return -1;
        }

        if(value % 2 == 0) {
            int cnt = index;
            int start = value - cnt * 2;
            if(start <= 0) return -1;
            return value + (n - index - 1ll) * 2;
        } else {
            if(index == 0) {
                if(index == n - 1) return value;
            } else {
                int cnt = index - 1;
                int start = (value - mn) - 2 * cnt;
                if(start <= 0) return -1;
                if(index == n - 1) return value;
            }
            return value + mn + 2 * (n - index - 2ll);
        }
    }
};
