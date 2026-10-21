class Solution {
public:
    int minOperations(string s) { //increasing
        string t = s;
        sort(t.begin(), t.end());

        if(s == t) {
            return 0;
        }

        if(s.size() == 2) {
            return -1;
        }

        vector<char> rmin(s.size());
        vector<char> lmax(s.size());
        for(int i = s.size() - 1; i >= 0; i--) {
            rmin[i] = s[i];
            if(i + 1 < s.size()) {
                rmin[i] = min(rmin[i], rmin[i + 1]);
            }
        }

        for(int i = 0; i < s.size(); i++) {
            lmax[i] = s[i];
            if(i) {
                lmax[i] = max(lmax[i], lmax[i - 1]);
            }
        }

        for(int i = 0; i < s.size() - 1; i++) {
            if(i > 0 && s[i] < s[i - 1]) {
                break;
            }
            if(s[i] <= rmin[i + 1]) {
                return 1;
            }
        }

        for(int i = s.size() - 1; i >= 1; i--) {
            if(i != s.size() - 1 && s[i] > s[i + 1]) {
                break;
            }
            if(lmax[i - 1] <= s[i]) {
                return 1;
            }
        }


        // always possible
        int n = s.size();
        if(s[0] != t[n - 1] || s[0] == t[n - 2]) {
            return 2;
        }

        if(s[n - 1] != t[0] || s[n - 1] == t[1]) {
            return 2;
        }

        return 3;
    }
};
