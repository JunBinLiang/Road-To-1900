class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& qu) {
        map<string, vector<pair<string, double>>> mp;
        int id = 0;
        for(int i = 0; i < equations.size(); i++) {
            string& a = equations[i][0], b = equations[i][1];
            mp[a].push_back({b, values[i]});
            mp[b].push_back({a, 1.0 / values[i]});
        }
        
        vector<double> ans;
        for(int i = 0; i < qu.size(); i++) {
            string& a = qu[i][0], b = qu[i][1];
            if(mp.find(a) == mp.end() || mp.find(b) == mp.end()) {
                ans.push_back(-1);
                continue;
            }
            
            queue<pair<string, double>> q;
            q.push({a, 1.0});
            set<string> vis;
            vis.insert(a);
            while(q.size()) {
                pair<string, double> p = q.front(); q.pop();
                string u = p.first; double v = p.second;
                if(u == b) {
                    ans.push_back(v);
                    break;
                }
                for(pair<string, double>& next : mp[u]) {
                    if(vis.find(next.first) == vis.end()) {
                        vis.insert(next.first);
                        q.push({next.first, v * next.second});
                    }
                }
            }
            if(ans.size() != i + 1) ans.push_back(-1);
        }
        return ans;
    }
};
