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

const int MOD = 1e9 + 7;
const int N = 5050;
long long f[N], C[N][N];

void init() {
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
      }
    }
}

int get(vector<int>& p, int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    f[0] = 1;
    for(int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= MOD; 
    }

    int s = 0;
    vector<int> p, pos(n + 1, -1);
    for(int i = 0; i < n; i++) {
        if(a[i] == -1) {
            s++;
        } else {
            pos[a[i]] = i;
        }
        p.push_back(s);
    }

    vector<int> vec;
    for(int i = 0; i <= n; i++) {
        if(pos[i]) {
            vec.push_back(i);
        }
    }
  
    //dp1[cnt][k] : how many subarrays with have "cnt" -1 and contain all number <= k
    vector<vector<int>> dp1(n + 1, vector<int>(n + 1));
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        vector<bool> vis(n + 1);
        int idx = 0;
        for(int j = i; j < n; j++) {
            if(a[j] == -1) cnt++;
            else {
                vis[a[j]] = true;
            }
            while(idx <= n) {
                if(pos[idx] == -1 || vis[idx]) {
                    idx++;
                } else {
                    break;
                }
            }
            if(idx) {
                dp1[cnt][idx - 1]++;
                //cout << i << "  " << j << "   : " << cnt << " " << idx - 1 << endl;
            }
        }
    }

    for(int cnt = 0; cnt <= n; cnt++) {
        for(int j = n - 1; j >= 0; j--) {
            dp1[cnt][j] += dp1[cnt][j + 1];
            dp1[cnt][j] %= MOD;
        }
    }
    
    /*for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            cout << dp1[i][j] << " ";
        } cout << endl;
    }
    cout << endl;*/

    int miss = 0;
    int l = n + 1, r = -1;
    vector<vector<int>> dp2(n + 1, vector<int>(n + 1));
    for(int i = 0; i < n; i++) {
        if(pos[i] == -1) {
            miss++;
        } else {
            l = min(l, pos[i]);
            r = max(r, pos[i]);
        }
        //cout << "m  " << i << " " << miss << "     " << l << " " << r << endl;
        if(r == -1) {
            for(int j = miss; j <= s; j++) {
                dp2[j][miss] += dp1[j][i];
                dp2[j][miss] %= MOD;
            }
        } else {
            int midcnt = get(p, l, r);
            for(int j = max(midcnt, miss); j <= s; j++) {
                dp2[j][miss] += dp1[j][i];
                dp2[j][miss] %= MOD;
            }
        }
    }

    long long ans = 0;
    for(int c1 = 0; c1 <= n; c1++) {
        for(int c2 = 0; c2 <= c1; c2++) {
            long long w = (C[c1][c2] * f[c2]);
            w %= MOD;
            w *= f[s - c2];
            w %= MOD;
            w *= dp2[c1][c2];
            w %= MOD;
            ans += w;
            ans %= MOD;
        }
    }
    cout << ans << endl;
}


int main() {
    init();
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
