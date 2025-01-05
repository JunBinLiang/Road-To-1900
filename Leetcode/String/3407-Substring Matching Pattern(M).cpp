class Solution {
public:
    bool hasMatch(string s, string p) {
        for(int i = 0; i < s.size(); i++) {
            string temp = "";
            for(int j = i; j < s.size(); j++) {
                temp += s[j];
                if(match(temp, p)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool match(string& s, string& p) {
        if(s.size() < p.size() - 1) {
            return false;
        } 
        int j = 0;
        for(int i = 0; i < p.size(); i++) {
            if(p[i] == '*') {
                j += (s.size() - (p.size() - 1));
            } else {
                if(s[j] != p[i]) {
                    return false;
                }
                j++;
            }
        }
        return true;
    }
};
