const int N = 1e4 * 21;
int id = 0;
int ans = 0;
int tr[N][12], p[N];
int ids[N];
int dp[(1 << 15)];
int cost[20][20], add[20][1 << 15];

void build(string& s, int t) {
    int u = 0;
    for(int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if(tr[u][c] == -1) {
            tr[u][c] = id++;
        }
        u = tr[u][c];
    }
    ids[u] = t;
}

int comp(const vector<int>& a, const vector<int>& sortedB) {
    int res = 0;
    for (int x : a) {
        res += lower_bound(sortedB.begin(), sortedB.end(), x)
             - sortedB.begin();
    }
    return res;
}

vector<int> dfs(int u) {
    vector<vector<int>> a;
    for(int i = 0; i < 12; i++) {
        if(tr[u][i] == -1) continue;
        vector<int> vec = dfs(tr[u][i]);
        sort(vec.begin(), vec.end());
        a.push_back(vec);
    }

    //flat
    vector<int> b;
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a[i].size(); j++) {
            b.push_back(a[i][j]);
        }
    }

    int sz = a.size();
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            cost[i][j] = comp(a[i], a[j]);
        }
    }

    for (int i = 0; i < sz; i++) {
        add[i][0] = 0;
        for (int mask = 1; mask < (1 << sz); mask++) {
            int bit = __builtin_ctz(mask);
            int prev = mask & (mask - 1);
            add[i][mask] = add[i][prev] + cost[bit][i];
        }
    }

    dp[0] = 0;
    for(int st = 1; st < (1 << sz); st++) {
        dp[st] = 1e9;
        for(int i = 0; i < sz; i++) {
            if((st & (1 << i)) > 0) {
                int pst = st ^ (1 << i);
                dp[st] = min(dp[st], dp[pst] + add[i][pst]);
            }
        }
    } 
    

    if(ids[u] != -1) {
        b.push_back(p[ids[u]]);
        for(int i = 0; i < b.size() - 1; i++) {
            if(b.back() > b[i]) ans++;
        }
    }
    ans += dp[(1 << sz) - 1];
    return b;
} 

class Solution {
public:
    int minInversions(vector<string>& a, vector<int>& b) {
        int n = a.size();
        id = 1;
        for(int i = 0; i <= n * 20; i++) {
            for(int j = 0; j < 12; j++) {
                tr[i][j] = -1;
            }
            ids[i] = -1;
        }

        for(int i = 0; i < a.size(); i++) {
            p[b[i]] = i;
        }


        for(int i = 0; i < a.size(); i++) {
            string& s = a[i];
            build(s, i);
        }

        ans = 0;
        dfs(0);
        return ans;
    }
};
