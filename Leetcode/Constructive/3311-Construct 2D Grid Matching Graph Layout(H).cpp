template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 50000 + 10;
vector<int> g[N];
bool vis[N];

vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool contain(vector<int>& a, int v) {
    return count(a.begin(), a.end(), v) > 0;
}

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        for(int i = 0; i < n; i++) {
            vis[i] = false;
            g[i].clear();
        }
        
        
        vector<int> in(n);
        for(auto& e : edges) {
            in[e[0]]++;
            in[e[1]]++;
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        vector<int> vec(5);
        for(int i = 0; i < n; i++) {
            vec[in[i]]++;
        }
        
        if(vec[1]) {
            vector<vector<int>> ans(1, vector<int>(n));
            for(int i = 0; i < n; i++) {
                if(in[i] == 1) {
                    ans[0][0] = i;
                    vis[i] = true;
                    break;
                }
            }
            
            for(int i = 1; i < n; i++) {
                for(int u : g[ans[0][i - 1]]) {
                    if(!vis[u]) {
                        ans[0][i] = u;
                        vis[u] = true;
                    }
                }
            }
            return ans;
        }
        
        int node = -1;
        for(int i = 0; i < n; i++) {
            if(in[i] == 2) {
                node = i;
            }
        }
        
        //build the first two rows
        vector<int> first, second;
        first.push_back(node);
        first.push_back(g[node][0]);
        second.push_back(g[node][1]);
        vis[node] = vis[g[node][0]] = vis[g[node][1]] = true;
        while(true) {
            int u = first.back();
            int v = second.back();
            bool add = false;
            for(int node : g[u]) {
                if(vis[node]) continue;
                vis[node] = true;
                add = true;
                if(contain(g[node], v)) {
                    second.push_back(node);
                } else {
                    first.push_back(node);
                }
            }
            if(!add) break;
        }
        
        vector<vector<int>> ans = {first, second};
        int M = first.size(), N = n / M;
    
        while(ans.size() != N) {
            vector<int> row;
            vector<int>& last = ans[ans.size() - 1];
            for(int u : g[last[0]]) {
                if(!vis[u]) {
                    vis[u] = true;
                    row.push_back(u);
                }
            }
            
            for(int i = 1; i < M; i++) {
                for(int u : g[row.back()]) {
                    if(vis[u]) continue;
                    if(contain(g[u], last[i])) {
                        row.push_back(u);
                        vis[u] = true;
                        break;
                    }
                }
            }
            ans.push_back(row);
        }
        
        return ans;
    }
};
