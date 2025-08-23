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

vector<int> L, R;
set<int> se;

int find(vector<int>& vec, int cur) {
    int l = 0, r = vec.size() - 1;
    int p1 = -1, p2 = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        auto it = se.upper_bound(vec[mid]);
        if(it == se.end()) {
            r = mid - 1;
            continue;
        }
        //cout << "gg " << *it << endl;
        int idx = *it;
        if(idx > cur) {
            r = mid - 1;
            continue;
        }
        if(L[idx] <= vec[mid] + 1 && R[idx] >= cur) {
            p1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if(p1 == -1) return 0;
    l = p1;
    r = vec.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        auto it = se.upper_bound(vec[mid]);
        if(it == se.end()) {
            r = mid - 1;
            continue;
        }
        int idx = *it;
        if(idx > cur) {
            r = mid - 1;
            continue;
        }
        if(L[idx] <= vec[mid] + 1 && R[idx] >= cur) {
            p2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    return p2 - p1 + 1;
}

void solve() {
    int n; long long t, x;
    cin >> n >> t >> x;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    L = vector<int>(n, 0);
    R = vector<int>(n, n - 1);
    vector<int> stk;
    for(int i = 0; i < n; i++) {
        while(stk.size() > 0 && a[i] > a[stk.back()]) {
            int j = stk.back(); stk.pop_back();
            R[j] = i - 1;
        }
        stk.push_back(i);
    }

    stk.clear();
    for(int i = n - 1; i >= 0; i--) {
        while(stk.size() > 0 && a[i] > a[stk.back()]) {
            int j = stk.back(); stk.pop_back();
            L[j] = i + 1;
        }
        stk.push_back(i);
    }

    se.clear();
    for(int i = 0; i < n; i++) {
        if(a[i] == x) {
            se.insert(i);
        }
    }
    
    int mx = -2000000000;
    long long s = 0;
    long long ans = 0;
    map<long long, vector<int>> mp;
    for(int i = 0; i < n; i++) {
        s += a[i];
        mx = max(mx, a[i]);
        if(s == t && mx == x) {
            ans++;
        }
        if(mp.find(s - t) != mp.end()) {
            vector<int>& vec = mp[s - t];
            int cnt = find(vec, i);
            ans += cnt;
        }
        mp[s].push_back(i);
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
