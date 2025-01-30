const int N = 1e5 + 10;
int p[N], w[N];
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        for(int i = 0; i < n; i++) {
            p[i] = i;
            w[i] = 1000000000;
        }
        
        for(auto& e : roads) {
            int u = e[0] - 1, v = e[1] - 1, c = e[2];
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) {
                p[r1] = r2;
                w[r2] = min(w[r2], c);
                w[r2] = min(w[r2], w[r1]);
            } else {
                w[r2] = min(w[r2], c);
            }
        }
        
        return w[find(0)];
    }
};
