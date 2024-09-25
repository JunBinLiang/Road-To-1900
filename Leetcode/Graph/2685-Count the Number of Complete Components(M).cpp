const int N = 60;
vector<int> g[N];
bool vis[N];
vector<int> component;

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        for(int i = 0; i < n; i++) g[i].clear();
        for(auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        memset(vis, 0, sizeof vis);
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                component.clear();
                dfs(i);
                bool good = true;
                for(int u : component) {
                    if(g[u].size() != component.size() - 1) {
                        good = false;
                    }
                }
                if(good) ans++;
            }
        }
        return ans;
    }
    
    void dfs(int u) {
        vis[u] = true;
        component.push_back(u);
        for(int v : g[u]) {
            if(!vis[v]) {
                dfs(v);
            }
        }
    }
};
