class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& a) {
        int n = a.size();
        vector<bool> left(n);
        left[0] = true;
        int j = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] >= a[i - 1]) {
                left[i] = true;
                j = i;
            } else {
                break;
            }
        }
        
        if(j == n - 1) {
            return 0;
        }
        
        int ans = (n - (j + 1));
        for(int i = n - 1; i >= 0; i--) {
            if(i + 1 < n && a[i] > a[i + 1]) break;
            while(j >= 0 && a[i] < a[j]) {
                j--;
            }
            ans = min(ans, n - (n - i) - (j + 1));
        }
        
        return ans;
    }
};
