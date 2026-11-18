const int N = 1e5 + 10;
vector<int> g[N];
map<int, long long> mps1[N], mps2[N];
int dep[N];
long long ans = 0;
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        for(int i = 0; i <= n; i++) {
            g[i].clear();
            mps1[i].clear();
            mps2[i].clear();
        }
        for(auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        ans = 0;
        dfs(group, -1, 0);
        return ans;
    }

    void dfs(vector<int>& a, int pa, int u) {
        mps1[u][a[u]] += 0;
        mps2[u][a[u]]++;
        
        for(int v : g[u]) {
            if(v == pa) continue;
            dfs(a, u, v);
            for(auto it = mps1[v].begin(); it != mps1[v].end(); it++) {
                int group = it -> first; long long val = it -> second;
                mps1[u][group] += (val + mps2[v][group]);
            }

            for(auto it = mps2[v].begin(); it != mps2[v].end(); it++) {
                int group = it -> first; long long val = it -> second;
                mps2[u][group] += val;
            }
        }

        for(int v : g[u]) {
            if(v == pa) continue;
            for(auto it = mps1[v].begin(); it != mps1[v].end(); it++) {
                int group = it -> first; long long val = it -> second + mps2[v][group]; // [group, count]
                ans += (val * (mps2[u][group] - mps2[v][group]));
            }
        }
    }

    
};
