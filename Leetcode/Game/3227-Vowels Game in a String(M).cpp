class Solution {
public:
    bool doesAliceWin(string s) {
        int cnt = 0;
        for(char& c : s) {
            if(isv(c)) {
                cnt++;
            }
        }
        
        if(cnt == 0) {
            return false;
        }
        return true;
    }

    bool isv(char c) {
        return c == 'a' || c == 'i' || c == 'e' || c == 'o' || c == 'u';
    }
};
