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
#include <deque>  

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int N = 105;

int C[305][305];
int dp[N][N * N];
void init() {
    C[0][0] = 1;
    for(int i = 1;i <= 300; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i - 1][j] + C[i - 1][j - 1] ) % MOD;
      }
    }
}

void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;
    }

    for(int i = 0; i <= n + 1; i++) {
        for(int j = 0; j <= m + 1; j++) {
            dp[i][j] = 0;
        }
    }

    dp[n][k] = 1; 
    for(int i = n - 1; i >= 1; i--) { 
        for(int used = 1; used <= m; used++) { //how many is used
            dp[i][used] += dp[i + 1][used];
            dp[i][used] %= MOD;
            if(dp[i + 1][used] == 0) continue;
            for(int c = 1; c + used <= m && c <= k; c++) {
                int slot = k - c + 1;
                int w = C[slot + c - 1][c];
                dp[i][c + used] += (((dp[i + 1][used] + 0ll) * w) % MOD );
                dp[i][c + used] %= MOD;
            }
        }
    }

    cout << dp[1][m] << endl;

}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

