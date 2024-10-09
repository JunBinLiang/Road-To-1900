const int N = 1e5 + 10;
vector<int> g[N];
int dfn[N], low[N];
int t = 0;
vector<vector<int>> bridges;
void tarjan(int pa, int u) {
    dfn[u] = low[u] = ++t;
    for(int v : g[u]) {
        if(!dfn[v]) {
            tarjan(u, v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) {
                bridges.push_back({u, v});
            }
        } else if(v != pa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            dfn[i] = low[i] = 0;
        }
        for(auto& e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        t = 0;
        bridges.clear();
        for(int i = 0; i < n; i++) {
            if(!dfn[i]) {
                tarjan(-1, i);
            }
        }
        return bridges;
    }
};
