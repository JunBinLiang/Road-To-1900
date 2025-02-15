class Solution {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            int x = i * i;
            if(ok(x, i)) {
                ans += x;
            }
        }
        return ans;
    }
    
    bool ok(int x, int k) {
        string s = to_string(x);
        bool ok = false;
        dfs(s, ok, 0, 0, k);
        return ok;
        
    }
    
    void dfs(string& s, bool& ok, int i, int sum, int k) {
        if(i >= s.size()) {
            if(sum == k) {
                ok = true;
            }
            return;
        }
        if(sum > k) {
            return;
        }
        int cur = 0;
        for(int j = i; j < s.size(); j++) {
            cur = cur * 10 + s[j] - '0';
            dfs(s, ok, j + 1, sum + cur, k);
        }
    }
};
