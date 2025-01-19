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
ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;

    long long ans = 1;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == '?') {
            ans *= i;
            ans %= MOD;
        }
    }

    if(s[0] != '?') cout << ans << endl;
    else cout << 0 << endl;

    for(int i = 0; i < m; i++) {
        int j; char c;
        cin >> j >> c;
        j--;

        if(j == 0) {
            s[j] = c;
        } else {
            if(s[j] == '?') {
                ans *= modInverse(j, MOD);
                ans %= MOD;
            }
            s[j] = c;
            if(s[j] == '?') {
                ans = ans * j;
                ans %= MOD;
            }
        }  

        if(s[0] != '?') cout << ans << endl;
        else cout << 0 << endl;
    }
}   


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
