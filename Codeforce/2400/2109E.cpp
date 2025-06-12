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
const int N = 510;
long long dp[N][N];
long long f[N][N];
void init() {
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for(int i = 1; i < N; i++) {
        f[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if(i % 2 == j % 2) {
                f[i][j] += f[i - 1][j - 1];
                f[i][j] %= MOD;
            }
        }
    }
    
    /*for(int i = 0; i <= 5; i++) {
        for(int j = 0; j <= 5; j++) {
            cout << f[i][j] << " ";
        } cout << endl;
    }
    cout << endl << endl;*/
}

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    reverse(s.begin(), s.end());
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        dp[i][0] = 1;
        for(int pk = 0; pk <= k; pk++) {
            for(int cnt = 1; cnt <= (pk + (s[i - 1] == '0')); cnt++) {
                if(cnt + pk > k) continue;
                if(s[i - 1] == '0') {
                    dp[i][cnt + pk] += (dp[i - 1][pk] * f[pk + 1][cnt]);
                } else {
                    dp[i][cnt + pk] += (dp[i - 1][pk] * f[pk][cnt]);
                }
                dp[i][cnt + pk] %= MOD;
            }
        }
        
        for(int ck = 1; ck <= k; ck++) {
            dp[i][ck] += dp[i - 1][ck];
            dp[i][ck] %= MOD;
        }
    }
    
    /*for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            cout << dp[i][j] << " ";
        } cout << endl;
    }*/
    cout << dp[n][k] << endl;
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
