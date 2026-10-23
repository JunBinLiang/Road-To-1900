class Solution {
public:
    int maxConsistentColumns(vector<vector<int>>& a, int limit) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> g(m);
        for(int c1 = 0; c1 < m; c1++) {
            for(int c2 = c1 + 1; c2 < m; c2++) {
                bool ok = true;
                for(int r = 0; r < n; r++) {
                    int d = abs(a[r][c1] - a[r][c2]);
                    if(d > limit) {
                        ok = false;
                        break;
                    }
                }
                if(ok) { // c1 - > c2  build graph, find longest path
                    g[c2].push_back(c1);
                }
            }
        }

        vector<int> dp(m, 1);
        for(int v = 0; v < m; v++) {
            for(int u : g[v]) { // u -> v
                dp[v] = max(dp[v], dp[u] + 1);
            }  
        }
        return *max_element(dp.begin(), dp.end());
    }
};
