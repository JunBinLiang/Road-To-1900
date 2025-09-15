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

const int INF = 1e6;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n, vector<int>(n + 1, INF));
    for(int k = 0; k <= n; k++) {
        dp[0][k] = 0;
    }
    
    for(int i = 1; i < n; i++) {
        for(int k = 0; k <= n; k++) {
            if(a[i] > a[i - 1]) {
                dp[i][k] = min(dp[i][k], dp[i - 1][k]);
            }
        }

        for(int k = 1; k <= n; k++) {
            dp[i][k] = min(dp[i][k], i);
            for(int j = i - 2; j >= 0; j--) {
                if(a[i] > a[j]) {
                    dp[i][k] = min(dp[i][k], i - j - 1 + dp[j][k - 1]);
                }
            }
        }

        if(i == n - 1) {
            for(int k = 1; k <= n; k++) {
                for(int j = i - 1; j >= 0; j--) {
                    dp[i][k] = min(dp[i][k], dp[j][k - 1] + (i - j));
                }   
            }
        }

        for(int k = 1; k <= n; k++) {
            dp[i][k] = min(dp[i][k], dp[i][k - 1]);
        }
    }

    for(int k = 1; k <= n; k++) {
        cout << dp.back()[k] << " ";
    }
    cout << endl;

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
