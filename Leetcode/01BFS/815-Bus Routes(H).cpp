const int INF = 1e9;
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int s, int t) {
        unordered_map<int, vector<pair<int, int>>> mp;
        unordered_map<int, int> d;
        int bus = 1000000 + 1;
        for(int i = 0; i < routes.size(); i++) {
            auto& route = routes[i];
            for(int j = 0; j < route.size(); j++) {
                int u = route[j];
                mp[bus].push_back({u, 0});
                mp[u].push_back({bus, 1});
            }
            bus++;
        }
        
        deque<int> dq;
        dq.push_back(s);
        d[s] = 0;
        while(dq.size()) {
            int u = dq.front(); dq.pop_front();
            for(pair<int, int> p : mp[u]) {
                int v = p.first, w = p.second;
                if(d.find(v) == d.end()) {
                    d[v] = INF;
                }
                if(d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    if(w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
        if(d.find(t) == d.end()) {
            return -1;
        }
        return d[t];
    }
};
