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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int xo = a[0];
    map<int, long long> mp;
    mp[0] = 3;
    for(int i = 1; i < n; i++) {
        int newxo = xo ^ a[i];

        if(mp.find(xo) != mp.end()) {
            mp[xo] *= 3;
            mp[xo] %= MOD;
        }

        if(mp.find(newxo) != mp.end()) {
            long long cnt = mp[newxo];
            mp[xo] += (cnt * 2);
            mp[xo] %= MOD;
        }
        xo = newxo;
    }

    int ans = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        ans += (it -> second);
        ans %= MOD;
    }
    cout << ans << endl;
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

