const int N = 50000 + 10;
vector<pair<int, int>> g[N];
vector<int> a;
vector<int> ans;
int dep[N], psum[N], path[N];
unordered_map<int, vector<int>> mp;
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        a = nums;
        ans = {-1, -1};
        int n = edges.size();
        for(int i = 0; i <= n; i++) {
            g[i].clear();
        }
        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        
        mp.clear();
        dfs(-1, 0, 0, 1, -1);
        return ans;
    }
    
    void update(int len, int nodes) {
        if(ans[0] == -1) {
            ans = {len, nodes};
            return;
        }
        if(len >= ans[0]) {
            if(len > ans[0]) ans = {len, nodes};
            else ans[1] = min(ans[1], nodes);
        }
    }
    
    void dfs(int pa, int u, int sum, int h, int last) {
        psum[u] = sum;
        dep[u] = h;
        path[h] = u;
        int newlast = last;
        if(mp[a[u]].size() > 0 && (last == -1 || dep[mp[a[u]].back()] > dep[last])) { //there is duplicate
            newlast = mp[a[u]].back();  
        } 
        mp[a[u]].push_back(u);
        
        if(newlast == -1) {
            update(psum[u], dep[u]);
        } else {
            update(psum[u] - psum[path[dep[newlast] + 1]], dep[u] - dep[newlast]);
        }
        
        for(auto& p : g[u]) {
            int v = p.first, w = p.second;
            if(v == pa) continue;
            dfs(u, v, sum + w, h + 1, newlast);
        }
        mp[a[u]].pop_back();
    }
};
