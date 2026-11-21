const int N = 1e5 + 10;
vector<int> g[N];
long long ans = 0;
class Solution {
public:
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& a) {
        for(int i = 0; i <= n; i++) g[i].clear();
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        ans = 0;
        map<int, int> mp;
        dfs(a, mp, -1, 0);
        return ans;
    }

    void dfs(vector<int>& a, map<int, int>& mp, int p, int u) {
        int x = a[u];
        int t = 1;
        for(int i = 2; i * i <= x; i++) {
            int cnt = 0;
            while(x % i == 0) {
                x /= i;
                cnt++;
            }
            if(cnt % 2 == 1) t *= i;
        }
        if(x > 1) t *= x;
        
        ans += mp[t];
        mp[t]++;

        for(int v : g[u]) {
            if(v == p) continue;
            dfs(a, mp, u, v);
        }

        mp[t]--;
    }
};
