#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;
const int N = 1e5 + 10;
int h[N], p[N];
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    } 
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }       

    long long ans = -1;
    long long l = 1, r = 1000000000ll;
    while(l <= r) {
        long long mid = l + (r - l) / 2;
        map<long long, int> mp;
        for(int i = 0; i < n; i++) {
            //Find the largest distance it can go
            long long left = 1, right = m, d = -1;
            while(left <= right) {
                long long mmid = left + (right - left) / 2;
                long long dam = mmid * mid;
                if(dam >= h[i]) {
                    d = mmid;
                    right = mmid - 1;
                } else {
                    left = mmid + 1;
                }
            }
            
            if(d != -1) {
                long long L = p[i] - (m - d), R = p[i] + (m - d);
                mp[L]++;
                mp[R + 1]--;
            }
        }

        bool ok = false;
        int s = 0;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            s += (it -> second);
            if(s >= k) ok = true;
        }
        if(ok) {
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

