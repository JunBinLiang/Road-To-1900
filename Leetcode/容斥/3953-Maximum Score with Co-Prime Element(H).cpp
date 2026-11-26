const int N = 1e5 + 100;
bool done = false;
bool is[N];
vector<int> p[N];
void init() {
    if(done) {
        return;
    }
    done = true;
    memset(is, 0, sizeof is);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        for(int j = i; j < N; j += i) {
            p[j].push_back(i);
            is[j] = true;
        }
    }
}

void dfs(vector<int>& prime, vector<pair<int, int>>& comb, int i, int x, int cnt) {
    if(i >= prime.size()) {
        if(x != 1) {
            comb.push_back({x, cnt});
        }
        return;
    }
    dfs(prime, comb, i + 1, x, cnt);
    dfs(prime, comb, i + 1, x * prime[i], cnt + 1);
}


class Solution {
public:
    int maxScore(vector<int>& a, int maxVal) {
        init();
        int mx = *max_element(a.begin(), a.end());
        mx = max(mx, maxVal);
        vector<int> cnt(mx + 1);
        set<int> s;
        for(int x : a) {
            s.insert(x);
            vector<int>& prime = p[x];
            vector<pair<int, int>> comb;
            dfs(prime, comb, 0, 1, 0);
            for(pair<int, int>& p : comb) {
                cnt[p.first]++;
            }
        }        

        int ans = 0;
        //not modify
        for(int x : a) {
            if(x == 1) {
                ans = max(ans, 1);
                continue;
            }
            vector<int>& prime = p[x];
            vector<pair<int, int>> comb;
            dfs(prime, comb, 0, 1, 0);
            int nonCop = 0;
            for(auto& p : comb) {
                if(p.second % 2 == 1) {
                    nonCop += cnt[p.first];
                } else {
                    nonCop -= cnt[p.first];
                }
            }
            int selectValue = x;
            ans = max(ans, selectValue - (nonCop - 1));
        }

        for(int i = 1; i <= maxVal; i++) {
            if(s.find(i) != s.end()) {
                continue;
            }
            vector<int>& prime = p[i];
            vector<pair<int, int>> comb;
            dfs(prime, comb, 0, 1, 0);
            int nonCop = 0;
            for(auto& p : comb) {
                if(p.second % 2 == 1) {
                    nonCop += cnt[p.first];
                } else {
                    nonCop -= cnt[p.first];
                }
            }
            int selectValue = i;
            if(nonCop == 0) {
                ans = max(ans, selectValue - 1);
            } else {
                ans = max(ans, selectValue - (nonCop - 1 + 1));
            }
        }
        return ans;
    }
};
