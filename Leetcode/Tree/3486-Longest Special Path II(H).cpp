const int N = 5e4 + 100;
vector<pair<int, int>> g[N];

int dis[N], h[N], revh[N], come[N]; //depth, height, reverse height
map<int, vector<int>> mp;
set<int> s;

class Solution {
public:
    vector<int> ans = {-1, 1000000000};
    vector<int> a;
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        a = nums;
        int n = a.size();
        for(int i = 0; i <= n; i++) g[i].clear();
        mp.clear();
        s.clear();

        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        dis[0] = 0;
        h[0] = 0;
        come[0] = 0;
        dfs(-1, 0);
        return ans;
    }

    void update(int u, int d, int count) {
        if(d >= ans[0]) {
            if(d == ans[0]) {
                ans[1] = min(ans[1], count);
            } else {
                ans[0] = d;
                ans[1] = count;
            }
        }
    }

    void add(int u) {
        vector<int>& vec = mp[a[u]];
        vec.push_back(h[u]);
        int sz = vec.size();
        //delete then add
        if(sz >= 4) {
            s.erase(vec[sz - 4]);
        }
        if(sz >= 2) {
            s.insert(vec[sz - 2]);
        }
        if(sz >= 3) {
            s.insert(vec[sz - 3]);
        }
    }

    void del(int u) {
        vector<int>& vec = mp[a[u]];
        vec.pop_back();
        int sz = vec.size();
        if(sz > 0) {
            s.erase(vec.back());
        }

        if(sz >= 2) {
            s.insert(vec[sz - 2]);
        }
        if(sz >= 3) {
            s.insert(vec[sz - 3]);
        }
    
    }

    void dfs(int pa, int u) {
        add(u);
        revh[h[u]] = u;

        if(s.size() >= 2) {
            auto it = s.end(); it--; it--;
            int ph = *it;
            update(u, dis[u] - dis[revh[ph]] - come[revh[ph]], h[u] - h[revh[ph]]);
        } else { 
            update(u, dis[u], h[u] + 1);
        }

        for(auto& e : g[u]) {
            int v = e.first, w = e.second;
            if(pa == v) continue;
            h[v] = h[u] + 1;
            dis[v] = dis[u] + w;
            come[u] = w;
            dfs(u, v);
        }
        del(u);
    }
};
