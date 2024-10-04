//7:05 - 7:12
class Solution {
public:
    vector<pair<int, int>> b, c;
    int ans = 1e9;
    int minimumMoves(vector<vector<int>>& a) {
        int n = a.size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(a[i][j] > 1) {
                    b.push_back({i, j});
                } else if(a[i][j] == 0) {
                    c.push_back({i, j});
                }
            }      
        }
        
        dfs(a, b, c, 0, 0);
        return ans;
    }
    
    void dfs(vector<vector<int>>& a, vector<pair<int, int>>& b, vector<pair<int, int>>& c, int i, int s) {
        if(i >= c.size()) {
            ans = min(ans, s);
            return;
        }
        for(int j = 0; j < b.size(); j++) {
            int row = b[j].first, col = b[j].second;
            if(a[row][col] > 1) {
                a[row][col]--;
                dfs(a, b, c, i + 1, s + abs(row - c[i].first) + abs(col - c[i].second));
                a[row][col]++;
            }
        }
    }
};
