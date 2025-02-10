class Solution {
public:
    string clearDigits(string s) {
        string res = "";
        for(int i = 0; i < s.size(); i++) {
            if(isD(s[i])) {
                if(res.size() > 0) res.pop_back();
            } else {
                res += s[i];
            }
        }
        return res;
    }
    
    bool isD(char c) {
        return c >= '0' && c <= '9';
    }
};
