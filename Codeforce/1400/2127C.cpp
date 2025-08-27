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

//12:11

bool same(vector<int>& a) {
    sort(a.begin(), a.end());
    return a[0] == a.back();
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    vector<pair<int, int>> c;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) swap(a[i], b[i]);
        c.push_back({a[i], b[i]});
    }

    long long ans = -1, s = 0;
    sort(c.begin(), c.end());
    for(int i = 0; i < n; i++) {
        s += (c[i].second - c[i].first);
    }

    for(int i = 0; i < n - 1; i++) {
        int x1 = c[i].first, y1 = c[i].second;
        int x2 = c[i + 1].first, y2 = c[i + 1].second;
        long long t = s - (y1 - x1) - (y2 - x2);
        vector<int> d = {x1, x2, y1, y2};
        sort(d.begin(), d.end());
        t += (d[3] + d[2] - d[0] - d[1]);
        if(ans == -1) ans = t;
        else ans = min(ans, t);
    }


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
