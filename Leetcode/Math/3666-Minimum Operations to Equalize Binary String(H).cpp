class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        vector<int> cnt(2);
        for(char c : s) {
            cnt[c - '0']++;
        }

        const int INF = 1e9;
        vector<int> d(n + 1, INF);
        int m = cnt[0];
        d[m] = 0;
        queue<int> q;
        q.push(m);
        
        vector<set<int>> indexsSet(2);
        for(int i = 0; i <= n; i++) { //unoccupy places
            if(i == m) continue;
            indexsSet[i % 2].insert(i);
        }

        while(q.size()) {
            int u = q.front();
            q.pop();
            int c1 = max(k - n + u, 0), c2 = min(u, k);
            int l = u + k - 2 * c2, r = u + k - 2 * c1;

            set<int>& indexs = indexsSet[(u + k) % 2];
            while(indexs.size() > 0) {
                auto it = indexs.upper_bound(l - 1);
                if(it == indexs.end()) break;
                int j = *it;
                if(j > r) break;
                indexs.erase(j);
                d[j] = d[u] + 1;
                q.push(j);
            }
        }
        return d[0] == INF? -1 : d[0];
    }
};
