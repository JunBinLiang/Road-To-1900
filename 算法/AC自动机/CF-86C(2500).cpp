#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct AcAutomation {
    int tr[2000 + 10][5];
    int ne[2000 + 10], len[2000 + 10], fa[2000 + 10];
    bool is[2000 + 10];
    int id = 1;
    void init() {
        memset(tr, 0, sizeof tr);
        memset(ne, 0, sizeof ne);
        memset(is, 0, sizeof is);
        memset(len, 0, sizeof len);
        memset(fa, -1, sizeof fa);
        id = 1;
    }

    void add(string& s) {
        int u = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if(tr[u][c] == 0) tr[u][c] = id++;
            fa[tr[u][c]] = u; //father
            u = tr[u][c];
            len[u] = i + 1;
        }
        is[u] = true;
    }
  
    void build() {
        queue<int> q;
        for(int i = 0; i < 4; i++) {
            if(tr[0][i] != 0) {
                q.push(tr[0][i]);
            }
        }
        while(q.size() > 0) {
            int u = q.front(); q.pop();
            for(int i = 0; i < 4; i++) {
                int c = tr[u][i];
                if(!c) {
                    tr[u][i] = tr[ne[u]][i];
                } else {
                    ne[c] = tr[ne[u]][i];
                    q.push(c);
                }
            }
        }
    }
} ac;

void to(string& s) {
    for(char& c : s) {
        if(c == 'A') c = 'a';
        if(c == 'C') c = 'b';
        if(c == 'G') c = 'c';
        if(c == 'T') c = 'd';
    }
}

const int MOD = 1e9 + 9;
long long dp[1100][110][15];
void solve() {
    ac.init();
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        string s;
        cin >> s;
        to(s);
        ac.add(s);
    } 

    ac.build();
    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int node = 0; node < ac.id; node++) {
            for(int c = 0; c < 4; c++) {
                int p = ac.tr[node][c];
                int pt = ac.tr[node][c];
                int len = 0;
                while(p) {
                    if(ac.is[p]) {
                        len = max(len, ac.len[p]);
                    }
                    p = ac.ne[p];
                }

                for(int unmatch = len - 1; unmatch >= 0; unmatch--) { //unmatch
                    dp[i][pt][0] += dp[i - 1][node][unmatch];
                    dp[i][pt][0] %= MOD;
                }

                for(int unmatch = len; unmatch <= 11; unmatch++) {
                    dp[i][pt][unmatch + 1] += dp[i - 1][node][unmatch];
                    dp[i][pt][unmatch + 1] %= MOD;
                }
            }
        }
    }
    
    long long ans = 0;
    for(int node = 0; node < ac.id; node++) {
        ans += dp[n][node][0];
        ans %= MOD;
    }
    cout << ans << endl;
    
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
