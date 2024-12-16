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

bool inter(pair<int, int>& p1, pair<int, int>& p2) {
    if(p1.first > p2.first) {
        return inter(p2, p1);
    }
    return p1.second >= p2.first;
}

pair<int, int> merge(pair<int, int>& p1, pair<int, int>& p2) {
    return {max(p1.first, p2.first), min(p1.second, p2.second)};
}

bool ok(vector<pair<int, int>>& a, int k) {
    pair<int, int> p = {0, 0};
    for(int i = 0; i < a.size(); i++) {
        p.first -= k;
        p.second += k;
        if(!inter(p, a[i])) {
            return false;
        }
        p = merge(p, a[i]);
    }
    
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    
    int l = 0, r = 1e9, ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(a, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
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
