const int N = 1e5 + 10;
vector<int> g[N];
int sz[N];
map<pair<int, int>, int> mp;
vector<int> ans;
class Solution {
public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string s, string t) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            sz[i] = 0;
        }
        mp.clear();
        for(int i = 0; i < edges.size(); i++) {
            auto& e = edges[i];
            int u = e[0], v = e[1];
            mp[{min(u, v), max(u, v)}] = i;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] != t[i]) {
                cnt++;
            }
        }
        if(cnt % 2 == 1) {
            return {-1};
        }

        ans.clear();
        dfs1(s, t, -1, 0);
        sort(ans.begin(), ans.end());
        return ans;
    }

    void dfs1(string& s, string& t, int p, int u) {
        if(s[u] != t[u]) { //flip need
            sz[u]++;
        }

        for(int v : g[u]) {
            if(v == p) continue;
            dfs1(s, t, u, v);
            sz[u] += sz[v];
            if(sz[v] % 2 == 1) {
                ans.push_back(mp[{min(u, v), max(u, v)}]);
            } 
        }
    }
};
