const int N = 1e5 + 10;
vector<int> g[N];
bool isp[N];

const int MOD = 1e9 + 7;
long long p[N];
int sz[N];
pair<long long, long long> dp[N];
int base = 101;

void dfs(string& s, int u) {
    sz[u] = 1;
    sort(g[u].begin(), g[u].end());
    reverse(g[u].begin(), g[u].end());
 
    long long h1 = s[u] - 'a' + 1;
    long long h2 = 0;

    for(int v : g[u]) {
        dfs(s, v);
        sz[u] += sz[v];
        h1 = h1 * p[sz[v]] + dp[v].first;
        h1 %= MOD;
    }
    
    for(int i = g[u].size() - 1; i >= 0; i--) {
        int v = g[u][i];
        h2 = h2 * p[sz[v]] + dp[v].second;
        h2 %= MOD;
    }

    h2 = h2 * base + (s[u] - 'a' + 1);
    h2 %= MOD;
    if(h1 == h2) {
        isp[u] = true;
    }
    dp[u] = {h1, h2};
}

class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = s.size();
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            isp[i] = false;
        }
        for(int i = 1; i < parent.size(); i++) {
            g[parent[i]].push_back(i);
        }
        
        p[0] = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = p[i - 1] * base;
            p[i] %= MOD;
        }
        
        dfs(s, 0);
        
        vector<bool> ans(n);
        for(int i = 0; i < n; i++) {
            ans[i] = isp[i];
        }
        return ans;
    }
};
