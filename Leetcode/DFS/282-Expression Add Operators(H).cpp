class Solution {
public:
    vector<string> ans;
    vector<string> addOperators(string s, int target) {
        string cur = "";
        long long d = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[0] == '0' && i != 0) break;
            cur += s[i];
            d = d * 10 + s[i] - '0';
            dfs(s, cur, i + 1, d, d, target);
        }
        return ans;
    }

    void dfs(string& s, string cur, int j, long long sum, long long p, int target) {
        if(j >= s.size()) {
            if(sum == target) {
                ans.push_back(cur);
            }
            return;
        }
        string temp = "";
        int d = 0;
        for(int i = j; i < s.size(); i++) {
            if(s[j] == '0' && i != j) break;
            d = d * 10 + s[i] - '0';
            temp += s[i];
            //+
            dfs(s, cur + "+" + temp, i + 1, sum + d, d, target);
            //-
            dfs(s, cur + "-" + temp, i + 1, sum - d, -d, target);
            //*
            dfs(s, cur + "*" + temp, i + 1, sum - p + (p * d), p * d, target);
        }
    }
};
