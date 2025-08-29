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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= k;
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i] %= k;
    }

    map<pair<int, int>, int> mp;
    for(int i = 0; i < n; i++) {
        int x = a[i];
        int y = abs(x - k);
        if(x > y) swap(x, y);
        mp[{x, y}]++;
    }


    for(int i = 0; i < n; i++) {
        int x = b[i], y = abs(x - k);
        if(x > y) swap(x, y);
        if(mp.find({x, y}) != mp.end() && mp[{x, y}] > 0) {
            mp[{x, y}]--;
        } else {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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
