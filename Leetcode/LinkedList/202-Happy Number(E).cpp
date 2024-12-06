class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = n;
        while(fast != 1) {
            slow = next(slow);
            fast = next(next(fast));
            if(slow == fast) {
                if(slow == 1) {
                    break; 
                }
                return false;
            }
        }
        return true;
    }
    
    int next(int n) {
        int ans = 0;
        while(n) {
            int d = n % 10;
            ans += (d * d);
            n /= 10;
        }
        return ans;
    }
};
