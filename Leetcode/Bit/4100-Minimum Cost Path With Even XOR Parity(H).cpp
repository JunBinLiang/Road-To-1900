const int N = 1e5 + 100;
vector<pair<int, int>> g[N];
long long xo[N], c[N];
long long INF = 1e16;
pair<long long, long long> dp[N]; // maintain the minimum cost with odd and even
long long ans = INF;
class Solution {
public:
    int minActivationCost(vector<vector<int>>& edges, vector<int>& values) {
        int n = edges.size();
        for(int i = 0; i <= n + 5; i++) {
            g[i].clear();
            xo[i] = 0;
            c[i] = 0;
            dp[i] = {INF, INF}; 
        }

        for(int i = 0; i < values.size(); i++) {
            values[i] = (count(values[i]) % 2);
        }
        
        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        xo[0] = values[0];
        c[0] = 0;
        
        if(xo[0] % 2 == 0) dp[0].second = 0;
        else dp[0].first = 0;
        dfs(values, -1, 0);

        ans = INF;
        dfs1(values, -1, 0);

        return ans > 1e15 ? -1 : ans;
    }

    int count(int x) {
        int ans = 0;
        for(int i = 0; i < 30; i++) {
            if(x & (1 << i)) ans++;
        }
        return ans;
    }

    void dfs(vector<int>& values, int pa, int u) {
        for(auto& e : g[u]) {
            int v = e.first, w = e.second;
            if(v == pa) continue;
            c[v] = c[u] + w;
            xo[v] = values[v] ^ xo[u];
            if(xo[v] == 0) { //even
                dp[v].second = c[v];
            } else {    
                dp[v].first = c[v];
            }
            dfs(values, u, v);
        }
    }

    // merge
    void dfs1(vector<int>& values, int pa, int u) {
        int cur = values[u] ^ xo[u];
        pair<long long, long long> prev = {INF, INF}; 
        for(auto& e : g[u]) {
            int v = e.first;
            if(v == pa) continue;
            dfs1(values, u, v);
            dp[u].first = min(dp[u].first, dp[v].first);
            dp[u].second = min(dp[u].second, dp[v].second);
            if(cur % 2 == 0) {
                ans = min(ans, dp[v].second - c[u]);
            } else {
                ans = min(ans, dp[v].first - c[u]);
            }

            if(values[u] % 2 == 0) {
                ans = min(ans, prev.first + dp[v].first - 2 * c[u]);
                ans = min(ans, prev.second + dp[v].second - 2 * c[u] );
            } else {
                ans = min(ans, prev.first + dp[v].second - 2 * c[u]);
                ans = min(ans, prev.second + dp[v].first - 2 * c[u]);
            }

            prev.first = min(prev.first, dp[v].first);
            prev.second = min(prev.second, dp[v].second);
        }
    }

};
