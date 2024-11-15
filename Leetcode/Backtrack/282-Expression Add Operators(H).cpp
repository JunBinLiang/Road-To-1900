class Solution {
public:
    int k;
    vector<string> ans;
    vector<string> ops = {"+", "-", "*"};
    vector<string> addOperators(string s, int target) {
        k = target;
        
        string temp = "";
        long long val = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[0] == '0' && i != 0) break;
            vector<string> exp;
            val = val * 10 + s[i] - '0';
            temp += s[i];
            exp.push_back(temp);
            dfs(s, exp, val, val, i + 1);
        }
        
        return ans;
    }
    
    void dfs(string& s, vector<string>& exp, long long sum, long long lastval, int index) {
        if(index >= s.size()) {
            if(sum == k) {
                string temp = "";
                for(string& t : exp) temp += t;
                ans.push_back(temp);
            }
            return;
        }   
        
        long long val = 0;
        for(int i = index; i < s.size(); i++) {
            if(i != index && s[index] == '0') break; //no leading zero allow
            
            val = val * 10 + (s[i] - '0');
            exp.push_back("+");
            exp.push_back(s.substr(index, i - index + 1));
            dfs(s, exp, sum + val, val, i + 1);
            exp.pop_back();
            exp.pop_back();
            
            exp.push_back("-");
            exp.push_back(s.substr(index, i - index + 1));
            dfs(s, exp, sum - val, -val, i + 1);
            exp.pop_back();
            exp.pop_back();
            
            exp.push_back("*");
            exp.push_back(s.substr(index, i - index + 1));
            dfs(s, exp, sum - lastval + (lastval * val), (lastval * val), i + 1);
            exp.pop_back();
            exp.pop_back();
        }
        
    }
};
