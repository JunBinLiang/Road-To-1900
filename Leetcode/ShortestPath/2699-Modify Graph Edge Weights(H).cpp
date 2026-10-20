const int N = 110;
const long long INF = 1e16;
vector<pair<int, int>> g[N];
long long dis[N];
bool st[N];


void dij(int s) {
    for(int i = 0; i < N; i++) {
        dis[i] = INF;
        st[i] = false;
    }

    dis[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, s});
    while(pq.size()) {
        auto p = pq.top(); pq.pop();
        int u = p.second;
        if(st[u]) continue;
        st[u] = true;
        for(auto& e : g[u]) {
            int v = e.first, w = e.second;
            if(dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int s, int t, int target) {
        //first check
        for(int i = 0; i < edges.size(); i++) {
            if(edges[i][2] == -1) {
                edges[i][2] = 1e9;
            }
        }

        for(int i = 0; i <= n; i++) {
            g[i].clear();
        }
        for(int i = 0; i < edges.size(); i++) {
            vector<int>& e = edges[i];
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        dij(s);
        if(dis[t] < target) {
            return {};
        }
        if(dis[t] == target) {
            return edges;
        }

        
        // add 1 gradually
        for(int i = 0; i < edges.size(); i++) {
            if(edges[i][2] == 1e9) {
                //turn to 1
                for(int j = 0; j < n; j++) g[j].clear();
                edges[i][2] = 1;
                for(int j = 0; j < edges.size(); j++) {
                    int u = edges[j][0], v = edges[j][1], w = edges[j][2];
                    g[u].push_back({v, w});
                    g[v].push_back({u, w});
                } 
                dij(s);
                if(dis[t] <= target) {
                    edges[i][2] += target - dis[t];
                    return edges;
                }
            }
        }
        return {};
    }
};
