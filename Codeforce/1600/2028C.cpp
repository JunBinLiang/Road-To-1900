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

long long get(vector<long long>& p, int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    long long ans = -1;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> L(n), R(n);
    vector<long long> p(n);
    for(int i = 0; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i - 1];
    }

    long long s = 0;
    for(int i = 0; i < n; i++) {
        s += a[i];
        if(s >= k) {
            L[i] = 1;
            s = 0;
        }
        if(i) {
            L[i] += L[i - 1];
        }
    }

    s = 0;
    for(int i = n - 1; i >= 0; i--) {
        s += a[i];
        if(s >= k) {
            R[i] = 1;
            s = 0;
        }
        if(i + 1 < n) {
            R[i] += R[i + 1];
        }
    }

    if(L.back() >= m) {
        ans = 0;
    }

    for(int i = 0; i < n; i++) {
        int cnt1 = 0;
        if(i) cnt1 = L[i - 1];
        int l = i, r = n - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int cnt2 = 0;
            if(mid + 1 < n) cnt2 = R[mid + 1];
            if(cnt1 + cnt2 >= m) {
                ans = max(ans, get(p, i, mid));
                l = mid + 1;
            } else {
                r = mid - 1;
            }
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
