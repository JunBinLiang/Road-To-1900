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
using ll = long long;
const long long INF = 1e9;

bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return min(p1.first, p1.second) < min(p2.first, p2.second);
}
const int N = 2e5 + 100;
bool dp[N][2][2]; //[i, swap, swap time]
void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first; 
    for(int i = 0; i < n; i++) cin >> a[i].second; 

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                dp[i][j][k] = false;
            }
        }
    }

    sort(a.begin(), a.end(), comp);
    dp[0][0][0] = dp[0][1][1] = true; 
    for(int i = 1; i < a.size(); i++) {
        int x1 = a[i - 1].first;
        int y1 = a[i - 1].second;
        int x2 = a[i].first;
        int y2 = a[i].second;

        //non swap
        //pre nonswap
        if(x2 > x1 && y2 > y1) {
            dp[i][0][0] |= dp[i - 1][0][0];
            dp[i][0][1] |= dp[i - 1][0][1];
        }

        //non swap
        //pre swap
        if(x2 > y1 && y2 > x1) {
            dp[i][0][0] |= dp[i - 1][1][0];
            dp[i][0][1] |= dp[i - 1][1][1];
        }

        //swap
        //pre nonswap
        if(y2 > x1 && x2 > y1) {
            dp[i][1][0] |= dp[i - 1][0][1];
            dp[i][1][1] |= dp[i - 1][0][0];
        }

        //swap
        //pre swap
        if(x2 > x1 && y2 > y1) {
            dp[i][1][0] |= dp[i - 1][1][1];
            dp[i][1][1] |= dp[i - 1][1][0];
        }
    }

    if(dp[n - 1][0][0] || dp[n - 1][1][0]) {
         cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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

