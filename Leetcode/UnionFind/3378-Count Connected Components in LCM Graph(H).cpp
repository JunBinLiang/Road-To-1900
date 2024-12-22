int find(vector<int>& p, int u) {
    return p[u] == u ? u : p[u] = find(p, p[u]);
}

const int N = 2e5 + 10;
vector<int> indexs[N];

class Solution {
public:
    int countComponents(vector<int>& a, int k) {
        int ans = 0;
        sort(a.begin(), a.end());
        while(a.size() > 0 && a.back() > k) {
            a.pop_back();
            ans++;
        }
        
        int n = a.size();
        vector<int> p(n);
        for(int i = 0; i < n; i++) {
            p[i] = i;
        }
        
        for(int i = 0; i <= k; i++) indexs[i].clear();
        
        for(int i = 0; i < n; i++) {
            for(int d = 1; d * d <= a[i]; d++) {
                if(a[i] % d != 0) continue;
                int g1 = d, g2 = a[i] / g1;
                indexs[g1].push_back(i);
                if(g1 == g2) continue;
                indexs[g2].push_back(i);
            }
        }
        
        for(int g = 1; g <= k; g++) {
            auto& vec = indexs[g];
            for(int i = 1; i < vec.size(); i++) {
                if((a[vec[0]] + 0ll) / g * a[vec[i]] <= k) {
                    int r1 = find(p, vec[0]), r2 = find(p, vec[i]);
                    if(r1 != r2) {
                        p[r1] = r2;
                    }
                }
            }
        }
                
        set<int> s;
        for(int i = 0; i < n; i++) {
            s.insert(find(p, i));
        }
        return ans + s.size();
    }
};
