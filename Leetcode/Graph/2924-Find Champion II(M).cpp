class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int> deg(n);
        for(auto& e : edges) {
            deg[e[1]]++;
        }
        
        int cnt = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            if(!deg[i]) {
                cnt++;
                ans = i;
            }
        }
        return cnt == 1 ? ans : -1;
    }
};
