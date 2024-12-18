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
const int INF = 1e9;
void solve() {
    string a, b, c;
    cin >> a >> b >> c;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
    dp[0][0] = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(i + j == 0) continue;
            if(i - 1 >= 0) {
                if(c[i + j - 1] == a[i - 1]) {
                  dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                } else {
                    dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j]);
                } 
            }

            if(j - 1 >= 0) {
                if(c[i + j - 1] == b[j - 1]) {
                  dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                } else {
                    dp[i][j] = min(dp[i][j], 1 + dp[i][j - 1]);
                }
            }
        }
    }
    cout << dp[n][m] << endl;
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
