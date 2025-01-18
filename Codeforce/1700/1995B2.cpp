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


void solve() {
    int n; long long k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) cin >> a[i].second;
    sort(a.begin(), a.end());

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        long long quan = k / a[i].first;
        quan = min(quan, a[i].second + 0ll);
        ans = max(ans, quan * a[i].first); //only buy a single type
    }

    for(int i = 0; i < n - 1; i++) {
        if(a[i].first + 1 != a[i + 1].first) continue;
        long long tot = (a[i].first + 0ll) * a[i].second + (a[i + 1].first  + 0ll) * a[i + 1].second;
        if(tot <= k) {
            ans = max(ans, tot);
            continue;
        }

        long long x1 = a[i].first, x2 = a[i + 1].first;
        long long q1 = a[i].second, q2 = a[i + 1].second;

        long long quan1 = k / x1;
        quan1 = min(quan1, q1);  
        long long w1 = quan1 * x1;
        long long quan2 = (k - w1) / x2;
        quan2 = min(quan2, q2);
        long long w2 = quan2 * x2;
        ans = max(ans, w1 + w2);
        long long remain = k - w1 - w2;
        q1 -= quan1;
        q2 -= quan2;
        ans = max(ans, w1 + w2 + min(remain, min(quan1, q2)));

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
