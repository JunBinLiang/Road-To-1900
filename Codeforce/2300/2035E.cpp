#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  


void solve() {
    long long x, y, z, k;
    cin >> x >> y >> z >> k;

    //damage = ax + by
    long long ans = 2e18;
    for(int a = 1; a <= min(z, 20000 + 10ll); a++) {
        //k, 2k, 3k, 4k ...
        int kcnt = a / k;
        long long dam = ((1ll + kcnt) * kcnt / 2) * k;
        long long cost = (x * a) + (kcnt * y);
        if(z > dam) {
            long long remain = z - dam;
            cost += ((remain / a) * y);
            if(remain % a != 0) cost += y;
        }
        ans = min(ans, cost);
    }

    for(int b = 1; b <= min(z, 20000 + 10ll); b++) {
        if((1ll + b) * b / 2 * k < z) continue;
        int l = 1, r = z;
        int acnt = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int a = mid;
            int kcnt = a / k;
            long long dam = ((1ll + kcnt) * kcnt / 2) * k;
            long long moreb = b - kcnt;
            if(moreb > 0)
                dam += (moreb * a);
            if(dam >= z) {
                acnt = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        long long cost = x * acnt + y * b;
        ans = min(ans, cost);
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
