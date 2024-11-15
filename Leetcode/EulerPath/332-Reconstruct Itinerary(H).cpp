/*
有向图欧拉路劲
*/

class Solution {
public:
    vector<string> path;
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> mp;
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for(auto& e : tickets) {
            mp[e[0]].push(e[1]);
        }
        
        string start = "JFK";
        dfs(start);
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
    
    void dfs(string u) {
        priority_queue<string, vector<string>, greater<string>>& pq = mp[u];
        while(pq.size() > 0) {
            string v = pq.top(); pq.pop();
            dfs(v);
            path.push_back(v);
        }
    }
};
