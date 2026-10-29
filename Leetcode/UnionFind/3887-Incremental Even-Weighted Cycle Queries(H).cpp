const int N = 50000 + 100;
vector<int> ch[N];
int newxo[N];
class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        vector<int> xo(n), p(n);
        for(int i = 0; i < n; i++) {
            p[i] = i;
            ch[i].clear();
            ch[i].push_back(i);
        }

        int ans = 0;
        for(auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            // find root
            int r1 = u, r2 = v;
            while(r1 != p[r1]) {
                r1 = p[r1];
            }
            while(r2 != p[r2]) {
                r2 = p[r2];
            }

            if(r1 != r2) {
                ans++;
                //merge
                if(ch[r1].size() > ch[r2].size()) {
                    swap(r1, r2);
                    swap(u, v);
                }
                //r1 -> r2
                p[r1] = r2;
                
                for(int c : ch[r1]) {
                    ch[r2].push_back(c);
                    newxo[c] = xo[c] ^ xo[u] ^ w ^ xo[v];
                }
                for(int c : ch[r1]) {
                    xo[c] = newxo[c];
                }
            } else {
                int x = xo[u] ^ xo[v] ^ w;
                if(x % 2 == 0) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
