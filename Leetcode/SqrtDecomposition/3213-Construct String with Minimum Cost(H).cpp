const int N = 5e4 + 100;
const int MOD = 1e9 + 7;
int base = 101;
long long p[N];
bool yes = false;

int tr[N][26];
pair<int, int> info[N * 26];
int id = 1;

void init() {
    if(yes) return;
    yes = true;
    memset(tr, -1, sizeof tr);
    for(int i = 0; i < N * 26; i++) {
        info[i] = {-1, -1};
    }
    p[0] = 1;
    for(int i = 1; i < N; i++) {
        p[i] = p[i - 1] * base;
        p[i] %= MOD;
    }
}

long long get(vector<long long>& h, int l, int r) {
    if(l == 0) return h[r];
    return (h[r] - (h[l - 1] * p[r - l + 1] % MOD) + MOD) % MOD;
}

void add(string& s, int len, int w) {
    int u = 0;
    for(int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if(tr[u][c] == -1) tr[u][c] = id++;
        u = tr[u][c];
    }
    if(info[u].first != -1) {
        info[u].second = min(info[u].second, w);
    } else {
        info[u] = {len, w};
    }
}

void clear() {
    for(int i = 0; i <= id; i++) {
        info[i] = {-1, -1};
        for(int j = 0; j < 26; j++) tr[i][j] = -1;
    }
    id = 1;
}


class Solution {
public:
    int minimumCost(string s, vector<string>& words, vector<int>& costs) {
        init();
        long long h = 0;
        vector<long long> h1(s.size());
        for(int i = 0; i < s.size(); i++) {
            h = h * base + (s[i] - 'a' + 1);
            h %= MOD;
            h1[i] = h;
        }
        
        
        unordered_map<int, vector<int>> mp;
        vector<pair<int, long long>> longs;
        for(int i = 0; i < words.size(); i++) {
            string& t = words[i];
            if(t.size() <= 250) {
                add(t, t.size(), costs[i]);
            } else {
                h = 0;
                for(int j = 0; j < t.size(); j++) {
                    h = h * base + (t[j] - 'a' + 1);
                    h %= MOD;
                }
                longs.push_back({i, h});
            }
        }
        
        vector<int> dp(s.size() + 1, -1);
        dp[s.size()] = 0; 
        for(int i = s.size() - 1; i >= 0; i--) {
            int u = 0, j = i;
            while(u != -1 && j < s.size()) {
                int c = s[j] - 'a';
                u = tr[u][c];
                j++;
                if(u != -1 && info[u].first != -1) {
                    int len = info[u].first, w = info[u].second;
                    if(i + len < dp.size() && dp[i + len] != -1) {
                        if(dp[i] == -1) dp[i] = w + dp[i + len];
                        else dp[i] = min(dp[i], w + dp[i + len]);
                    }
                }
            }
            
            for(pair<int, long long> p : longs) {
                int j = p.first;
                int len = words[j].size();
                if(i + len < dp.size() && get(h1, i, i + len - 1) == p.second && dp[i + len] != -1) {
                    if(dp[i] == -1) dp[i] = costs[j] + dp[i + len];
                    else dp[i] = min(dp[i], costs[j] + dp[i + len]);
                }
            }
            
        }
        clear();
        return dp[0];
    }
};
