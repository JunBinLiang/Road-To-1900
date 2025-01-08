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

const int N = 210;
long long dp[N][N][N];
long long best[N][N];
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> a(n, vector<long long>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            best[i][j] = 1e18;
            for(int t = 0; t <= m; t++) { 
                dp[i][j][t] = 1e18;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int t = 0; t < m; t++) { //number of times shift
                int x = a[i][(j + t) % m];
                if(i == 0 && j == 0) {
                    dp[i][j][t] = x + (k + 0ll) * t;
                }   
                if(i - 1 >= 0) {
                    dp[i][j][t] = min(dp[i][j][t], best[i - 1][j] + x + ((k + 0ll) * t));
                }
                if(j - 1 >= 0) {
                    dp[i][j][t] = min(dp[i][j][t], dp[i][j - 1][t] + x);
                }
                best[i][j] = min(best[i][j], dp[i][j][t]);
            }
        }
    }
    cout << best[n - 1][m - 1] << endl;
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
