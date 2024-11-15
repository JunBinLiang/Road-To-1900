class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) {
            return "1";
        }
        string s = "1";
        while(n > 1) {
            n--;
            string temp = "";
            for(int i = 0; i < s.size(); i++) {
                int j = i;
                int cnt = 0;
                while(j < s.size() && s[i] == s[j]) {
                    cnt++;
                    j++;
                }
                temp += to_string(cnt) + s[i];
                i = j - 1;
            }
            s = temp;
        }        
        
        return s;
    }
};
