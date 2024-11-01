class Solution {
public:
    int triangleNumber(vector<int>& a) {
        int ans = 0;
        sort(a.begin(), a.end());
        
        for(int i = 0; i < a.size(); i++) {
            int r = i + 2;
            for(int j = i + 1; j < a.size(); j++) {
                while(r < a.size() && a[i] + a[j] > a[r]) {
                    r++;
                }
                if(r > j) {
                    ans += (r - j - 1);
                }
            }
        }
        return ans;
    }
};
