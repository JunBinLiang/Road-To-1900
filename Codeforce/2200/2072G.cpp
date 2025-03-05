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
#include <deque>  

using namespace std;
const int MOD = 1e9 + 7;

long long cal1(int n, int k) {
    long long ans = 0;
    while(n > 0) {
        int m = n % k;
        n /= k;
        ans = ans * k + m;
        ans %= MOD;
    }
    return ans;
}

long long cal2(int L, int R, int n) {
    long long ans = 0;
    int c = n / L;
    int t = n % R;
    int x = R;
    int sz = (R - L + 1);
    
    long long s1 = (((x + 0ll) * t) % MOD) * sz;
    s1 %= MOD;

    long long s2 = (((x + 0ll) * c) % MOD) * (((sz - 1ll) * sz / 2) % MOD);
    s2 %= MOD;

    long long s3 = (((sz - 1ll) * sz / 2) % MOD) * t;
    s3 %= MOD;

    long long s4 = (((sz - 1ll) * (sz) * (2 * (sz - 1) + 1) / 6) % MOD) * c;
    s4 %= MOD;
    //(x) (t)
    //(x - 1) (t - 1)
    //(x - 2) (t - 2)
    //(x - 3) (t - 3)
    //...
    //(L) (t - y)
    
    ans += s1;
    ans %= MOD;
    ans += s2;
    ans %= MOD;
    ans -= s3;
    if(ans < 0) ans += MOD;
    ans -= s4;
    if(ans < 0) ans += MOD;
    return ans;
}

void solve() {
    long long n, k;
    cin >> n >> k;

    long long ans = 0;
    if(k >= n) {
        ans += ((k - n) % MOD * n);
        ans %= MOD;
        k = n;
    }

    int s = sqrt(n);
    int t = 2;
    for(int i = 2; i <= min(k, s + 5ll); i++) {
        ans += cal1(n, i);
        ans %= MOD;
        t = i + 1;
    }
    
    //cout << "gg " << t << "  " << ans << endl;

    //[t : k]
    int R = k;
    for(int i = n / k; i <= s; i++) {
        int l = t, r = R; 
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(mid * (i + 1) > n) {
                p = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if(p != -1) {
            //[p : R]
            int cnt = (R - p + 1);
            long long sum = cnt;
            sum %= MOD;
            sum *= i;
            sum %= MOD;
            ans += (sum);
            ans %= MOD;

            //calculate MOD
            /*
            example : 30  
                      9   3   3
                      8   3   6
            */
            ans += cal2(p, R, n);
            ans %= MOD;

            R = p - 1;
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
