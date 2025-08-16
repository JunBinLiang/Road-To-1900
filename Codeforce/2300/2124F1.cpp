#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int MOD = 998244353;
const int N = 110;
set<int> s[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++) s[i].clear();
    for(int i = 0; i < m; i++) {
        int j, val;
        cin >> j >> val;
        s[j].insert(val);
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j >= 1; j--) {
            int sz = i - j + 1;
            vector<int> b(sz);
            for(int t = 0; t < b.size(); t++) {
                b[t] = t + 1;
            }
            bool ok1 = true;
            for(int t = 0; t < b.size(); t++) {
                if(s[j + t].find(b[t]) != s[j + t].end()) {
                    ok1 = false;
                    break;
                }
            }
            if(ok1) {
                for(int c = 0; c <= n; c++) {
                    dp[i][sz] += dp[j - 1][c];
                    dp[i][sz] %= MOD;
                }
            }
            
            for(int shift = 1; shift < sz; shift++) {
                vector<int> c(b.begin() + 1, b.end());
                c.push_back(b[0]);
                b = c;
                bool ok2 = true;
                for(int t = 0; t < b.size(); t++) {
                    if(s[j + t].find(b[t]) != s[j + t].end()) {
                        ok2 = false;
                        break;
                    }
                }
                if(ok2) {
                    for(int c = 0; c <= n; c++) {
                        if(shift == c) continue;
                        dp[i][0] += dp[j - 1][c];
                        dp[i][0] %= MOD;
                    }
                }
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= n; i++) {
        ans += dp.back()[i];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
