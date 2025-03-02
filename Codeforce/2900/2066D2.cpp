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

int get(vector<int>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<int> a(m);
    vector<int> last(101, -1), cnt(101, 0);
    for(int i = 0; i < m; i++) {
        cin >> a[i];
        if(a[i] > 0) {
            last[a[i]] = i;
            cnt[a[i]]++;
        }
    }

    vector<vector<int>> p(n + 1, vector<int>(m));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            if(j) p[i][j] = p[i][j - 1];
            if(a[j] >= i) {
                p[i][j]++;
            }
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s <= m; s++) {
            for(int take = 0; take <= k; take++) {
                if(s < take) continue;
                
                if(take < cnt[i]) continue;

                if ((s - take) + k - 1 < last[i]) { //can not satisfy contidion
                    continue;
                }

                if((s - take) + k  > m) { //make sure not place outside
                    continue;
                }
                int put = take - cnt[i];
                int spot = k - p[i][(s - take) + k - 1];
                if(spot < 0) continue;
                dp[i][s] += (((dp[i - 1][s - take] + 0ll) * C[spot][put]) % MOD);
                dp[i][s] %= MOD;
            }
        }
    }

    cout << dp[n][m] << endl;
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

