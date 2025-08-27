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
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int s = a[i] + a[j];
            //x <= s - 1
            //s + x - 1 >= mx      x >= mx - s + 1
            int R = s - 1, L = a.back() - s + 1;
            if(L > R) continue;
            int l = j + 1, r = n - 1;
            int p1 = -1, p2 = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[mid] >= L) {
                    p1 = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }

            l = j + 1; r = n - 1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[mid] <= R) {
                    p2 = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if(p1 != -1 && p2 != -1) {
                ans += (p2 - p1 + 1);
            }
            
        }
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
