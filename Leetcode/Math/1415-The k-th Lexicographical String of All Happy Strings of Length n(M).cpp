char get(vector<char>& a, int k, char last) {
    for(char c : a) {
        if(c == last) continue;
        k--;
        if(k == 0) return c;
    }
    return ' ';
}

class Solution {
public:
    string getHappyString(int n, int k) {
        string ans = "";
        vector<int> p(n + 1);
        p[0] = 1;
        for(int i = 1; i < p.size(); i++) {
            p[i] = p[i - 1] * 2;
        }
        
        if(k > 3 * p[n - 1]) {
            return "";
        }
        
        vector<char> b = {'a', 'b', 'c'};
        while(k && ans.size() != n) {
            if(ans.size() == 0) {
                if(k <= p[n - 1]) {
                    ans += 'a';
                } else if(k <= 2 * p[n - 1]) {
                    k -= p[n - 1];
                    ans += 'b';
                } else {
                    k -= 2 * p[n - 1];
                    ans += 'c';
                }
            } else {
                char last = ans.back();
                if(k <= p[n - ans.size() - 1]) {
                    ans += get(b, 1, last);
                } else {
                    k -= p[n - ans.size() - 1];
                    ans += get(b, 2, last);
                }
            }
        }
        return ans;
    }
};
