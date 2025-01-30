const int N = 510;
vector<int> g[N];
int col[N];
bool ok = true;
void dfs(vector<int>& comp, int u, int c) {
    comp.push_back(u);
    col[u] = c;
    for(int v : g[u]) {
        if(col[v] == -1) {
            dfs(comp, v, c ^ 1);
        } else {
            if(col[u] == col[v]) {
                ok = false;
            }
        }
    }
}

int bfs(int n, int u) {
    int ans = 0;
    vector<int> d(n, -1);
    queue<int> q;
    q.push(u);
    d[u] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        ans = max(ans, d[u]);
        for(int v : g[u]) {
            if(d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return ans;
}

class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            col[i] = -1;
        }
        for(auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        vector<vector<int>> a;
        ok = true;
        for(int i = 0; i < n; i++) {
            if(col[i] == -1) {
                vector<int> comp;
                dfs(comp, i, 0);
                a.push_back(comp);
                if(!ok) {
                    return -1;
                }
            }
        }
        
        int ans = 0;
        for(auto& comp : a) {
            int best = 0;
            for(int u : comp) {
                best = max(best, bfs(n, u));
            }
            ans += best;
        }
        
        return ans;
    }
};
