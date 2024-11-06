class Solution {
public:
    int bitcount(int n) {
        int cnt = 0;
        for(int i = 0; i < 9; i++) {
            if(n & (1 << i)) {
                cnt++;
            }
        }
        return cnt;
    }
    
    bool canSortArray(vector<int>& a) {
        vector<int> c;
        for(int i = 0; i < a.size(); i++) {
            int j = i;
            vector<int> b;
            while(j < a.size() && bitcount(a[j]) == bitcount(a[i])) {
                b.push_back(a[j]);
                j++;
            }
            sort(b.begin(), b.end());
            for(int x : b) c.push_back(x);
            i = j - 1;
        }
        
        for(int i = 1; i < c.size(); i++) {
            if(c[i] < c[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
};
