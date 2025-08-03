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

void solve() {
    long long n, L, R, k;
    cin >> n >> L >> R >> k;
    if(n % 2 == 1) {
        cout << L << endl;
        return;
    }

    if(L == R || n == 2) {
        cout << -1 << endl;
        return;
    }

    int b = -1;
    for(int i = 0; i < 61; i++) {
        if(L & (1ll << i)) b = i;
    }

    long long x = L, y = 1ll << (b + 1);
    if(y > R) {
        cout << -1 << endl;
        return;
    }

    if(k <= n - 2) cout << x << endl;
    else cout << y << endl;
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
