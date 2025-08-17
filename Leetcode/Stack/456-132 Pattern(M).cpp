class Solution {
public:
    const int INF = 1e9;
    bool find132pattern(vector<int>& a) {
        int n = a.size();
        vector<int> stk;
        int s2 = -INF;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] < s2) {
                return true;
            }
            while(stk.size() && a[i] > stk.back()) {
                int last = stk.back(); stk.pop_back();
                s2 = max(s2, last);
            }
            stk.push_back(a[i]);
        }        
        return false;
    }
};
