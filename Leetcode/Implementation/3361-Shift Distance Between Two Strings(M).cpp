class Solution {
public:
    long long shiftDistance(string s, string t, vector<int>& w1, vector<int>& w2) {
        long long ans = 0;
        for(int i = 0; i < s.size(); i++) {
            int c1 = s[i] - 'a';
            int c2 = t[i] - 'a';
            long long t1 = 0, t2 = 0;
            while(c1 != c2) {
                t1 += w1[c1];
                c1++;
                c1 %= 26;
            }
            c1 = s[i] - 'a';
            while(c1 != c2) {
                t2 += w2[c1];
                c1--;
                if(c1 < 0) c1 += 26;
            }
            ans += min(t1, t2);
        }
        return ans;
    }
};
