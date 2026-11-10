const int N = 1050;
vector<pair<int, int>> g[N];

class Solution {
public:
    int minimumThreshold(int n, vector<vector<int>>& edges, int s, int t, int k) {
        for(int i = 0; i <= n; i++) g[i].clear();
        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        } 

        int l = 0, r = 1e9;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            // do 0 - 1 bfs
            const int INF = 1e5;
            vector<int> d(n, INF);
            deque<int> q;
            q.push_back(s);
            d[s] = 0;
            while(q.size()) {
                int u = q.front();
                q.pop_front();
                for(auto& e : g[u]) {
                    int v = e.first, w = e.second;
                    if(w <= mid) w = 0;
                    else w = 1;
                    if(d[u] + w < d[v]) {
                        d[v] = d[u] + w;
                        if(w == 0) q.push_front(v);
                        else q.push_back(v);
                    }
                } 
            }
            if(d[t] <= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
