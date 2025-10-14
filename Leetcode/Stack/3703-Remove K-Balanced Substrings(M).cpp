class Solution {
public:
    string removeSubstring(string s, int k) {
        vector<pair<char, int>> stk;
        for(int i = 0; i < s.size(); i++) {
            int j = i;
            int cnt = 0;
            while(j < s.size() && s[i] == s[j]) {
                cnt++;
                j++;
            }
            if(s[i] == '(') {
                while(stk.size() && stk.back().first == '(') {
                    cnt += stk.back().second;
                    stk.pop_back();
                }
                stk.push_back({'(', cnt});
            } else {
                while(stk.size() > 0) {
                    if(stk.back().first == ')') {
                        cnt += stk.back().second;
                        stk.pop_back();
                    } else {
                        if(stk.back().second >= k && cnt >= k) {
                            stk.back().second -= k;
                            cnt -= k;
                            if(stk.back().second == 0) stk.pop_back();
                        } else {
                            break;
                        }
                    }
                }
                if(cnt) stk.push_back({')', cnt});
            }
            i = j - 1;
        }
        string ans = "";
        for(auto& p : stk) {
            for(int i = 0; i < p.second; i++) {
                ans += p.first;
            }
        }
        return ans;
        
    }
};
