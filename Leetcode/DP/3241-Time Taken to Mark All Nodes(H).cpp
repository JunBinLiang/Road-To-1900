const int N = 1e5 + 10;
vector<int> g[N];
int t[N], dp[N];
vector<int> ans;
set<pair<int, int>> s[N];
class Solution {
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        ans = vector<int>(n);
        for(int i = 0; i < n; i++) {
            g[i].clear();
            s[i].clear();
        }
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        

        dfs(-1, 0);
        ans[0] = dp[0];
        dfs1(-1, 0);
        //cout << endl;
        return ans;
    }
    
    void dfs(int pa, int u) {
        if(pa == -1) {
            t[u] = 0;
        } else {
            if(u % 2 == 0) t[u] = t[pa] + 2;
            else t[u] = t[pa] + 1;
        }
        dp[u] = t[u];
        s[u].insert({dp[u], u});
        for(int v : g[u]) {
            if(v == pa) continue;
            dfs(u, v);
            dp[u] = max(dp[u], dp[v]);
            s[u].insert({dp[v], v});
        }
    }
    
    void dfs1(int pa, int u) {
        if(pa != -1) {
            s[u].clear();
            for(int v : g[u]) {
                if(v == pa) continue;
                s[u].insert({dp[v] - t[u], v});
            }
            
            int add = 0;
            if(pa % 2 == 1) add = 1;
            else add = 2;
            
            s[pa].erase({dp[u] - t[pa], u});
            auto it = s[pa].end();
            it--;
            s[u].insert({it -> first + add, pa});
            s[pa].insert({dp[u] - t[pa], u});
            it = s[u].end();
            it--;
            ans[u] = it -> first;
        }
        for(int v : g[u]) {
            if(v == pa) continue;
            dfs1(u, v);
        }
    }
};
