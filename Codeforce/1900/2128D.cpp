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
bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.second < p2.second;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];    


    vector<long long> dp(n);
    dp[n - 1] = 1;
    if(a[n - 2] > a[n - 1]) {
        dp[n - 2] = 3;
    } else {
        dp[n - 2] = 2;
    }
    
    for(int i = n - 3; i >= 0; i--) {
        if(a[i] > a[i + 1]) {
            int sz = n - i;
            dp[i] = sz + dp[i + 1];
        } else {
            dp[i] = 1 + dp[i + 1];
        }
    }

    long long ans = 0;
    for(long long x : dp) {
        ans += x;
        //cout << x << " ";
    }
    //cout << endl;
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
