class Solution {
public:
    vector<vector<string>> ans;
    
    vector<vector<string>> solveNQueens(int n) {
        vector<string> grid(n, string(n, '.'));
        
        vector<bool> col(n);
        set<int> s1, s2;
        dfs(n, 0, grid, col, s1, s2);
        return ans;
    }
    
    void dfs(int n, int i,  vector<string>& grid, vector<bool>& col, set<int>& s1, set<int>& s2) {
        if(i >= n) {
            ans.push_back(vector<string>(grid.begin(), grid.end()));
            return;
        }
        
        //fill ith row
        for(int j = 0; j < n; j++) {
            //try to fill grid[i][j]
            if(col[j] == false && (s1.find(i + j) == s1.end()) && (s2.find(i - j) == s2.end())) {
                grid[i][j] = 'Q';
                col[j] = true;
                s1.insert(i + j);
                s2.insert(i - j);
                
                dfs(n, i + 1, grid, col, s1, s2);
                
                grid[i][j] = '.';
                col[j] = false;
                s1.erase(i + j);
                s2.erase(i - j);
            }
        }
    }
};
