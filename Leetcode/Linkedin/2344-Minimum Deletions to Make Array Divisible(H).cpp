//2:19 - 2:22
class Solution {
public:
    int minOperations(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        int g = b[0];
        for(int i = 0; i < b.size(); i++) {
            g = __gcd(g, b[i]);
        }
        
        for(int i = 0; i < a.size(); i++) {
            if(g % a[i] == 0) {
                return i;
            }
        }
        return -1;
    }
};
