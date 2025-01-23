const int N = 300 * 300;
int p[N], sz[N];

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void merge(int u, int v) {
    int r1 = find(u), r2 = find(v);
    if(r1 != r2) {
        p[r1] = r2;
        sz[r2] += sz[r1];
    }
}

class Solution {
public:
    int countServers(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        for(int i = 0; i < n * m; i++) {
            p[i] = i;
            sz[i] = 1;
        }
        
        for(int i = 0; i < n; i++) {
            int pj = -1;
            for(int j = 0; j < m; j++) {
                if(a[i][j]) {
                    if(pj != -1) {
                        merge(i * m + pj, i * m + j);
                    }
                    pj = j;
                }
            }
        }
        
        for(int j = 0; j < m; j++) {
            int pi = -1;
            for(int i = 0; i < n; i++) {
                if(a[i][j]) {
                    if(pi != -1) {
                        merge(pi * m + j, i * m + j);
                    }
                    pi = i;
                }
            }
        }
        
        int ans = 0;
        set<int> s;
        for(int i = 0; i < n * m; i++) {
            int r = find(i);
            if(s.find(r) == s.end() && sz[r] > 1) {
                ans += sz[r];
                s.insert(r);
            }
        }
        return ans;
    }
    
};
