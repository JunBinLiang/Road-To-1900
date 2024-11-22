#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
const int N = 2e5 + 100;
const int MOD = 998244353;
int a[N];
long long dp[1000000 + 10];

/*
C(4, 1) = 4
C(4, 2) = 6
C(4, 3) = 4
C(4, 4) = 1

C(5, 1) = 5
C(5, 2) = 10
C(5, 3) = 10
C(5, 4) = 5
C(5, 5) = 1

C(6, 1) = 6
C(6, 2) = 15
C(6, 3) = 20
C(6, 4) = 15
C(6, 5) = 6
C(6, 6) = 1
*/

void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    memset(dp, 0, sizeof dp);
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int> div; //divisors
        for(int j = 2; j * j <= x; j++) {
            if(x % j == 0) {
                while(x % j == 0) x /= j;
                div.push_back(j);
            }
        }
        if(x > 1) div.push_back(x);
        long long add = 0;
        
        int sz = div.size();
        for(int st = 1; st < (1 << sz); st++) {
            int cnt = 0, p = 1;
            for(int j = 0; j < sz; j++) {
                if(st & (1 << j)) {
                    cnt++;
                    p *= div[j];
                }
            }
            add += dp[p];
            add %= MOD;
        }

        if(i == 1) add = 1;
        if(i == n) ans = add;

        for(int st = 1; st < (1 << sz); st++) {
            int cnt = 0, p = 1;
            for(int j = 0; j < sz; j++) {
                if(st & (1 << j)) {
                    cnt++;
                    p *= div[j];
                }
            }
            if(cnt % 2 == 1) {
                dp[p] += add;
                dp[p] %= MOD;
            } else {
                dp[p] -= add;
                if(dp[p] < 0) dp[p] += MOD;
            }
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

