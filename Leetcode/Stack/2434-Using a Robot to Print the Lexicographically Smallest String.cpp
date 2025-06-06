class Solution {
public:
    string robotWithString(string s) {
        int n = s.size();
        vector<char> mins(n);
        for(int i = n - 1; i >= 0; i--) {
            mins[i] = s[i];
            if(i + 1 < n) mins[i] = min(mins[i + 1], s[i]);
        }

        string t = "", ans = "";
        for(int i = 0; i < n; i++) {
            t += s[i];
            while(t.size() > 0 && i + 1 < n && t.back() <= mins[i + 1]) {
                ans += t.back();
                t.pop_back();
            }
        }
        reverse(t.begin(), t.end());
        ans += t;
        return ans;
    }
};
