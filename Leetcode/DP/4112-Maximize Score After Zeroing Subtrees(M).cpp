const int N = 1e5 + 10;
vector<int> g[N];
int dp[N];
class Solution {
public:
    int maxScore(vector<int>& p, vector<int>& op, vector<int>& score) {
        int n = p.size();
        for(int i = 0; i < n; i++) {
            g[i].clear();
            dp[i] = 0;
        }
        for(int i = 1; i < n; i++) {
            g[p[i]].push_back(i);
        }

        dfs(op, score, -1, 0);
        return dp[0];
    }

    void dfs(vector<int>& ops, vector<int>& a, int p, int u) {
        dp[u] = a[u];
        vector<int> b;
        for(int v : g[u]) {
            if(v == p) continue;
            dfs(ops, a, u, v);
            b.push_back(dp[v]);
        }
        sort(b.begin(), b.end());
        if(ops[u] == 0) { //at most 1
            int index = 0;
            if(b.size() > 0 && b[0] < 0) {
                index++;
            }
            for(int i = index; i < b.size(); i++) {
                dp[u] += b[i];
            }
        } else {
            for(int i = 1; i < b.size(); i++) {
                dp[u] += b[i]; 
            } 
        }
    }
};
