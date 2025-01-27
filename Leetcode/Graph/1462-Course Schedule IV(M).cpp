class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<int>> g(n);
        vector<vector<bool>> vis(n, vector<bool>(n));
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[v].push_back(u); //reverse graph
        }
        
        vector<bool> ans;
        for(int i = 0; i < n; i++) {
            dfs(g, vis, i, i);
        } 
        
        for(auto& q : queries) {
            ans.push_back(vis[q[1]][q[0]]);
        }
        return ans;
    }
    
    void dfs(vector<vector<int>>& g, vector<vector<bool>>& vis, int root, int u) {
        if(vis[root][u]) return;
        vis[root][u] = true;
        for(int v : g[u]) {
            dfs(g, vis, root, v);
        }
    }
};
