class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int ans = 1e9;
        vector<set<int>> sets(languages.size());
        for(int i = 0; i < languages.size(); i++) {
            sets[i] = set<int>(languages[i].begin(), languages[i].end());
        }
        for(int i = 1; i <= n; i++) {
            //teach language i
            vector<bool> vis(languages.size());
            int need = 0;
            for(vector<int>& e : friendships) {
                int u = e[0] - 1, v = e[1] - 1;
                if(hasCommon(sets[u], sets[v])) continue;
                if(sets[u].find(i) == sets[u].end() && !vis[u]) {
                    vis[u] = true;
                    need++;
                }
                if(sets[v].find(i) == sets[v].end() && !vis[v]) {
                    vis[v] = true;
                    need++;
                }
            }
            ans = min(ans, need);
        }
        return ans;
    }

    bool hasCommon(set<int>& s1, set<int>& s2) {
        for(int x : s1) {
            if(s2.find(x) != s2.end()) {
                return true;
            }
        }
        return false;
    }
};
