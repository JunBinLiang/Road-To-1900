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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];

    int o = 0;
    for(int x : b) o |= x;
    int mx = 0, mn = 0;
    if(n % 2 == 0) {
        for(int x : a) {
            mn ^= (x | o);
        }
        for(int x : a) mx ^= x;

    } else {
        for(int x : a) {
            mx ^= (x | o);
        }
        for(int x : a) mn ^= x;
    }
    cout << mn << " " << mx << endl;
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
