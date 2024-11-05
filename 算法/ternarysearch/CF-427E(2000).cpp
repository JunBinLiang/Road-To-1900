#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  

long long get(vector<pair<int, int>>& a, int mid, int m) {
    vector<int> b, c;
    int start = a[mid].first;
    for(int i = mid + 1; i < a.size(); i++) {
        for(int j = 0; j < a[i].second; j++) b.push_back(a[i].first);
    }
    for(int i = 0; i < mid; i++) {
        for(int j = 0; j < a[i].second; j++) c.push_back(a[i].first);
    }

    long long s = 0;
    reverse(b.begin(), b.end());
    for(int i = 0; i < b.size(); i++) {
        if(i % m == 0) {
            s += ((b[i] - start + 0ll) * 2);
        }
    }

    //reverse(c.begin(), c.end());
    for(int i = 0; i < c.size(); i++) {
        if(i % m == 0) {
            s += ((start - c[i] + 0ll) * 2);
        }
    }

    return s;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(a.size() == 0 || x != a.back().first) {
            a.push_back({x, 1});
        } else {
            a.back().second++;
        }
    }

    int l = 0, r = a.size() - 1;
    long long ans = 2e18;
    while(l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = l + (r - l) / 3 * 2;
        long long c1 = get(a, mid1, m);
        long long c2 = get(a, mid2, m);
        ans = min(ans, c1);
        ans = min(ans, c2);
        if(c1 <= c2) {
            r = mid2 - 1;
        } else {
            l = mid1 + 1;
        }
    }
    cout << ans << endl;
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
