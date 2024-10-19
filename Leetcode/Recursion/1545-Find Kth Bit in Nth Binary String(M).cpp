class Solution {
public:
    char findKthBit(int n, int k) {
        int s = 0;
        vector<int> a;
        for(int i = 0; i < n; i++) {
            s = s * 2 + 1;
            a.push_back(s);
        }
        return (char)(dfs(a, a.size() - 1, k) + '0');
    }
    
    int dfs(vector<int>& a, int i, int k) {
        if(i == 0) {
            return 0;
        }
        int half = a[i] / 2;
        if(k == half + 1) return 1;
        else if(k <= half) return dfs(a, i - 1, k);
        else return dfs(a, i - 1, half - (k - half - 1) + 1) ^ 1;
    }
};
