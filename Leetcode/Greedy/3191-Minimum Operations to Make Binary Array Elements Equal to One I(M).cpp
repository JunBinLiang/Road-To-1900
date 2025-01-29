class Solution {
public:
    int minOperations(vector<int>& a) {
        int ans = 0;
        for(int i = 0; i + 2 < a.size(); i++) {
            if(a[i] == 0) {
                ans++;
                a[i + 1]++;
                a[i + 2]++;
                a[i + 1] %= 2;
                a[i + 2] %= 2;
            }
        }
        return (a[a.size() - 2] == 1 && a[a.size() - 1] == 1) ? ans : -1;
    }
};
