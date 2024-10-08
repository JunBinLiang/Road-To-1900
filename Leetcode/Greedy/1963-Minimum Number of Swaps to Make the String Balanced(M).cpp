class Solution {
public:
    int minSwaps(string s) {
        int cnt = 0, ans = 0;
        vector<int> stk;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '[') {
                stk.push_back(i);
            }
        }
        
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '[') cnt++;
            else {
                if(cnt == 0) {
                    ans++;  
                    cnt++;
                    swap(s[i], s[stk.back()]);
                    stk.pop_back();
                } else {
                    cnt--;
                }
            }
        }
        return ans;
    }
};
