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

const int MOD = 998244353;

void solve() {
    long long n, b, c;
    cin >> n >> b >> c;
    if(b == 0 && c == 0) {
        if(n == 1) {
            cout << 0 << endl;
            return;
        }
        if(n == 2) {
            cout << 1 << endl;
            return;
        }
        cout << -1 << endl;
        return;
    }

    if(b == 1 && c == 0) {
        cout << 0 << endl;
        return;
    }

    if(b == 0) {
        if(c + 2 < n) {
            cout << -1 << endl;
        } else {
            if(n - 1 < c) cout << n << endl;
            else cout << max(1ll, n - 1) << endl;
        }
        return;
    }

    long long ans = -1;
    long long l = c, r = 1e18;
    //[0 : n - 1]
    if(n - 1 >= c) {
        ans = n - (1 + (n - 1 - c) / b);
    } else {
        ans = n;
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
