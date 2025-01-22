vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> vis(n, vector<bool>(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j]) {
                    q.push({i, j});
                    vis[i][j] = true;
                    a[i][j] = 0;
                }
            }
        }
        
        while(q.size()) {
            int sz = q.size();
            for(int i = 0; i < sz; i++) {
                auto [r, c] = q.front(); q.pop();
                for(auto& d : dir) {
                    int newr = r + d[0], newc = c + d[1];
                    if(newr < 0 || newr >= n || newc < 0 || newc >= m || vis[newr][newc]) continue;
                    vis[newr][newc] = true;
                    a[newr][newc] = 1 + a[r][c];
                    q.push({newr, newc});
                }
            }
        }
        return a;
    }
};
