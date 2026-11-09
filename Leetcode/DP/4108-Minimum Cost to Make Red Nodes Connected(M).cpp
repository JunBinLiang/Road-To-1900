const int N = 1e5 + 10;
const long long INF = 1e15;
vector<int> g[N];
int sz[N];
long long dp[N][3];
class Solution {
public:
    long long minCost(int n, string s, vector<vector<int>>& edges) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            sz[i] = 0;
            dp[i][0] = dp[i][1] = dp[i][2] = INF;
        }

        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(-1, 0);
        dfs1(s, -1, 0);
        long long ans = min(dp[0][0], min(dp[0][1], dp[0][2]));
        return ans;
    }

    void dfs(int p, int u) {
        sz[u] = 1;
        for(int v : g[u]) {
            if(v == p) continue;
            dfs(u, v);
            sz[u] += sz[v];
        }
    }

    //[no red, has red, has red and current is read]
    void dfs1(string& s, int p, int u) { 
        if(g[u].size() == 1 && u != 0) { //leave
            if(s[u] == 'R') {
                dp[u][0] = 1;
                dp[u][2] = 0;
            } else {
                dp[u][0] = 0;
                dp[u][2] = 1;
            }
        }

        vector<int> childs;
        for(int v : g[u]) {
            if(v == p) continue;
            dfs1(s, u, v);
            childs.push_back(v);
        }

        if(s[u] == 'R') {
            dp[u][0] = sz[u];
            dp[u][2] = 0;
            long long totBlue = 0;
            for(int v : childs) {
                dp[u][0] += dp[v][0];
                dp[u][2] += min(dp[v][2], dp[v][0]);
                totBlue += dp[v][0];
            }
            for(int v : childs) {
                dp[u][1] = min(dp[u][1], sz[u] + min(dp[v][1], dp[v][2]) + totBlue - dp[v][0]);
            }
        } else {
            dp[u][0] = 0;
            dp[u][2] = sz[u];
            long long totBlue = 0;
            for(int v : childs) {
                dp[u][0] += dp[v][0];
                dp[u][2] += min(dp[v][2], dp[v][0]);
                totBlue += dp[v][0];
            }
            for(int v : childs) {
                dp[u][1] = min(dp[u][1], min(dp[v][1], dp[v][2]) + totBlue - dp[v][0]);
            }
        }
    }
};
