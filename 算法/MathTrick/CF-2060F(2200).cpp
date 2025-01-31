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

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        long long q = a / m;
        long long t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

//Math : https://en.wikipedia.org/wiki/Hockey-stick_identity
//C(r, r) + C(r + 1, r) + ... C(n, r) = C(n + 1, r + 1)

long long cal(int n, int r) {
    //C(r, r) + C(r + 1, r) + ... C(n, r) = C(n + 1, r + 1)
    n++;
    r++;
    long long p1 = 1, p2 = 1;
    for(int i = 1; i <= r; i++) {
        p2 *= i;
        p2 %= MOD;
    }

    for(int i = 1; i <= r; i++) {
        p1 *= (n - i + 1);
        p1 %= MOD;
    }

    p2 = modInverse(p2, MOD);
    return (p1 * p2) % MOD;
}

const int N = 1e5 + 10;
long long dp[N][18];
void init() {
    memset(dp, 0, sizeof dp);
    for(int i = 2; i < N; i++) {
        vector<int> a;
        int w = i;
        for(int j = 2; j * j <= w; j++) {
            if(i % j != 0) continue;
            a.push_back(j);
            if(i / j != j) a.push_back(i / j);
        }
        
        dp[i][1] = 1;
        for(int j = 2; j < 18; j++) {
            for(int d : a) {
                dp[i][j] += dp[i / d][j - 1];
                dp[i][j] %= MOD;
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            cout << m << " ";
            continue;
        }
        int w = i;
        int tot = 0;
        for(int j = 2; j * j <= w; j++) {
            if(w % j != 0) continue;
            int cnt = 0;
            while(w % j == 0) {
                w /= j;
                cnt++;
            }
            tot += cnt;
        }
        if(w > 1) {
            tot++;
        }

        long long ans = 0;
        for(int space = 1; space <= min(tot, m); space++) {
            long long ways = cal(m, space);
            ans += ((dp[i][space] * ways) % MOD);
            ans %= MOD;
        }
        cout << ans << " ";
    }
    cout << endl;
}    


int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

