class Solution {
public:
    bool canAliceWin(int n) {        
        for(int i = 10; i >= 1; i--) {
            if(n < i) {
                if(i % 2 == 0) {
                    return false;
                } else {
                    return true;
                }
            }
            n -= i;
        }
        return true;
    }
};
