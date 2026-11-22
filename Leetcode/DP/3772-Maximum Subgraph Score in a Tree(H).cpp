const int N = 1e5 + 10;
vector<int> g[N];
int dp[N];
int ans = -1e9;
class Solution {
public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            dp[i] = 0;
        }
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs1(good, -1, 0);
        dfs2(-1, 0);
        vector<int> ans;
        for(int i = 0; i < n; i++) ans.push_back(dp[i]);
        return ans;
    }

    void dfs1(vector<int>& good, int p, int u) {
        if(good[u] == 1) dp[u] = 1;
        else dp[u] = -1;
        for(int v : g[u]) {
            if(v == p) continue;
            dfs1(good, u, v);
            dp[u] += max(0, dp[v]);
        }
    }

    void dfs2(int p, int u) {
        if(p != -1) { //tree rotate
            int pbest = dp[p];
            int subtract = max(0, dp[u]);
            pbest -= subtract;
            dp[u] += max(pbest, 0);
            ans = max(ans, dp[u]);
        }
        for(int v : g[u]) {
            if(p == v) continue;
            dfs2(u, v);
        }
    }
};
