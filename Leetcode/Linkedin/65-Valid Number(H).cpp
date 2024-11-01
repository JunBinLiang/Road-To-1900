class Solution {
public:
    bool isNumber(string s) {
        /*
        2e10.1 => false
        2.123e => false
        2.123e1 => true
        2.123e0 => true
        .123e0
        can have leading zero => 0089
        */
        if(s[0] == '+' || s[0] == '-') { //eliminate + -
            return good(s.substr(1, s.size() - 1));
        } else {
            return good(s);
        }
    }
    
    bool good(string s) { //is number without optional + -
        if(s.size() == 0) return false;
        int dotp = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '.') {
                if(dotp != -1) return false;
                dotp = i;
            }
        }
        
        if(dotp == -1) {
            return goodInteger(s);
        } else {
            if(s.size() == 1) return false;
            string first = s.substr(0, dotp);
            string second = s.substr(dotp + 1, s.size() - (dotp + 1));
            for(char c : first) {
                if(c == 'e' || c == 'E') return false;
            }
            if(first.size() == 0) {
                 if(second.size() > 0 && (second[0] == 'e' || second[0] == 'E')) return false;  
            }
            return goodInteger(first) && goodDecimal(second); 
        }
        
    }
    
    bool goodInteger(string s) {
        int epos = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == 'e' || s[i] == 'E') {
                if(epos != -1) return false;
                epos = i;
            } else {
                if(epos == -1 && !isdigit(s[i])) return false;
            }
        }
        if(epos == -1) return true;
        return epos != 0 && goodAfterE(s.substr(epos + 1, s.size() - (epos + 1)));
    }
    
    bool goodDecimal(string s) {
        int epos = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == 'e' || s[i] == 'E') {
                if(epos != -1) return false;
                epos = i;
            } else {
                if(epos == -1 && !isdigit(s[i])) return false;
            }
        }
        if(epos == -1) return true;
        return goodAfterE(s.substr(epos + 1, s.size() - (epos + 1)));
    }
    
    bool goodAfterE(string s) {
        if(s.size() == 0) return false;
        if(s[0] == '+' || s[0] == '-') s = s.substr(1, s.size() - 1);
        if(s.size() == 0) return false;
        for(int i = 0; i < s.size(); i++) {
                if(!isdigit(s[i])) return false;
        }
        return true;
    }
    
    bool isdigit(char c) {
        return c - '0' >= 0 && c - '0' < 10;
    }
};
