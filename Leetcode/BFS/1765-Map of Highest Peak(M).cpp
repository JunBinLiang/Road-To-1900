vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector<vector<int>> ans(n, vector<int>(m, -1));
        queue<pair<int, int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] == 1) {
                    q.push({i, j});
                    ans[i][j] = 0;
                }
            }
        }
        
        int level = 0;
        while(q.size()) {
            int sz = q.size();
            level++;
            for(int i = 0; i < sz; i++) {
                pair<int, int> p = q.front(); q.pop();
                for(auto& d : dir) {
                    int r = p.first + d.first, c = p.second + d.second;
                    if(r < 0 || r >= n || c < 0 || c >= m || ans[r][c] != -1) {
                        continue;
                    }
                    ans[r][c] = level;
                    q.push({r, c});
                }
            }
        }   
        return ans;
    }
};
