class Solution {
public:
    string compressedString(string s) {
        string ans = "";
        for(int i = 0; i < s.size(); i++) {
            int j = i, cnt = 0;
            while(j < s.size() && cnt < 9 && s[i] == s[j]) {
                cnt++; j++;
            }
            ans += to_string(cnt);
            ans += s[i];
            i = j - 1;
        }
        return ans;
    }
};
