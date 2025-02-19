class Solution {
public:
    int countSubarrays(vector<int>& a, int k) {
        int n = a.size(), ans = 0;
        int po = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] == k) {
                po = i;
            }
        }
        
        int s = 0;
        int cnt = 0;
        unordered_map<int, int> mp[2];
        for(int i = po - 1; i >= 0; i--) {
            if(a[i] < k) s--;
            else s++;
            cnt++;
            mp[cnt % 2][s]++;
        }
        
        s = 0;
        cnt = 0;
        for(int i = po; i < n; i++) {
            cnt++;
            if(a[i] < k) s--;
            else if(a[i] > k)s++;
            
            if(cnt % 2 == 1 && s == 0) {
                ans++;
            }
            
            if(cnt % 2 == 0 && s == 1) {
                ans++;
            }
            
            if(cnt % 2 == 0) {
                ans += mp[1][-s];
                ans += mp[0][1 - s];
            } else {
                ans += mp[0][-s];
                ans += mp[1][1 - s];
            }
        }
        
        
        return ans;
    }
};
