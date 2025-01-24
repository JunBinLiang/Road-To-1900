class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> revg(n);
        vector<int> in(n);
        for(int u = 0; u < n; u++) {
            for(int v : graph[u]) {
                revg[v].push_back(u);
                in[u]++;
            }
        }
        
        vector<int> ans;
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(!in[i]) {
                q.push(i);
            }
        }
        
        while(q.size()) {
            int u = q.front(); q.pop();
            ans.push_back(u);
            for(int v : revg[u]) {
                in[v]--;
                if(!in[v]) {
                    q.push(v);
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
