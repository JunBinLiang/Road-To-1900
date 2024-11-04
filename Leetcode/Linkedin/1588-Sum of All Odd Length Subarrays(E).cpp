class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& a) {
        int ans = 0, s = 0, odd = 0, even = 0;
        int oddcnt = 0, evencnt = 0;
        for(int i = 0; i < a.size(); i++) {
            s += a[i];
            if(i % 2 == 0) ans += ((s * oddcnt) - odd);
            else ans += (s * evencnt - even);
            
            if(i % 2 == 0) ans += s;
            
            if(i % 2 == 0) even += s, evencnt++;
            else odd += s, oddcnt++;
        }
        return ans;
    }
};
