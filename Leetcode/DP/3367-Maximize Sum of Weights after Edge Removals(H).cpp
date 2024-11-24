const int N = 1e5 + 10;
vector<pair<int, int>> g[N];
long long dp[N][2];
int k;

bool comp(pair<long long, long long>& p1, pair<long long, long long>& p2) {
    return (p1.first - p1.second) > (p2.first - p2.second);
}

void dfs(int pa, int u) {
    if(g[u].size() == 1 && pa != -1) {
        dp[u][0] = dp[u][1] = 0;
        return;
    }
    
    long long s = 0;
    long long ans = 0;
    vector<pair<long long, long long>> a;
    for(pair<int, int>& p : g[u]) {
        int v = p.first, w = p.second;
        if(v == pa) continue;
        dfs(u, v);
        a.push_back({dp[v][1] + w, dp[v][0]}); //taken, not taken
        s += dp[v][0];
    }
    
    sort(a.begin(), a.end(), comp);
    dp[u][0] = dp[u][1] = s;
    long long t = 0;
    long long ss = s;
    for(int i = 0; i < min(k - 1, (int)(a.size())); i++) {
        ss -= a[i].second;
        t += a[i].first;
        dp[u][1] = max(dp[u][1], ss + t);
    }
    
    ss = s;
    t = 0;
    for(int i = 0; i < min(k, (int)(a.size())); i++) {
        ss -= a[i].second;
        t += a[i].first;
        dp[u][0] = max(dp[u][0], ss + t);
    }
}


class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int K) {
        int n = edges.size() + 1;
        k = K;
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            dp[i][0] = dp[i][1] = 0;
        }
        
        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        
        dfs(-1, 0);
        long long ans = max(dp[0][0], dp[0][1]);
        return ans;
    }
};
