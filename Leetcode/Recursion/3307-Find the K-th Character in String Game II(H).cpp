class Solution {
public:
    char kthCharacter(long long k, vector<int>& a) {
        if(k == 1) return 'a';
        int n = a.size();
        long long s = 0;
        int t = 1000;
        for(int i = 0; i < n; i++) {
            s *= 2;
            if(s >= k) {
                t = i + 1;
                break;
            }
        }

        while(a.size() > 61) a.pop_back();
        
        int ans = dfs(a, k, a.size() - 1);
        return (char)(ans + 'a');
        
    }
    
    int dfs(vector<int>& a, long long k, int i) {
        if(i < 0) {
            return 0;
        }
        
        long long half = 1ll << (i);
        if(k <= half) {
            return dfs(a, k, i - 1);
        } else {
            int op = a[i];
            if(op == 0) {
                return dfs(a, k - half, i - 1);
            } else {
                return (1 + dfs(a, k - half, i - 1) % 26);
            }
        }
    }
};
