#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;
//2:53 - 3:26
const int MOD = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long ans = 1;
    int g = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > a[i - 1]) {
            cout << 0 << endl;
            return;
        }
        if(g % a[i] != 0) {
            cout << 0 << endl;
            return;
        }

        if(g == a[i]) {
            ans *= (m / a[i]);
            ans %= MOD;
            continue;
        }

        int temp = g / a[i];
        vector<int> pri;
        for(int j = 2; j * j <= temp; j++) {
            if(temp % j == 0) {
                pri.push_back(j);
                while(temp % j == 0 ) {
                    temp /= j;
                }
            }
        }
        if(temp > 1) pri.push_back(temp);
      
        long long cnt = m / a[i];
        int sz = pri.size();
        for(int st = 1; st < (1 << sz); st++) {
            int bit = 0;
            int p = 1;
            for(int j = 0; j < sz; j++) {
                if(st & (1 << j)) {
                    bit++;
                    p *= pri[j];
                }
            }
            int c = m / (p * a[i]);
            if(bit % 2 == 1) cnt -= c;
            else cnt += c;
        }
        ans *= cnt;
        ans %= MOD;
        g = a[i];
    }

    cout << ans << endl;
}   

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
