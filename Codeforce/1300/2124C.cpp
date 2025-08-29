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

//11:16

long long lcm(long long x, long long y) {
    return x * y / __gcd(x, y);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = -1;
    for(int i = n - 2; i >= 0; i--) {
        if(a[i] > a[i + 1] || a[i + 1] % a[i] != 0) {
            int g = __gcd(a[i], a[i + 1]);
            long long x = a[i] / g;
            if(ans == -1) ans = x;
            else ans = lcm(ans, x);
        }
    }

    if(ans == -1) ans = 1;
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
