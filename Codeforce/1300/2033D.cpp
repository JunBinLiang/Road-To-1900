#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>


using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    long long s = 0;
    vector<int> dp(n);
    map<long long, int> mp;
    for(int i = 0; i < n; i++) {
        s += a[i];
        if(s == 0) {
            dp[i] = 1;
        }
        if(mp.find(s) != mp.end()) {
            dp[i] = max(dp[i], 1 + dp[mp[s]]);
        }
        if(i) dp[i] = max(dp[i], dp[i - 1]);
        mp[s] = i;
    }

    cout << dp.back() << endl;
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
