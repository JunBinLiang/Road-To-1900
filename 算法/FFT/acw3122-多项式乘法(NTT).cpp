#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

//https://www.luogu.com/article/blkewk6b
namespace NTT {
    const int MOD = 998244353;
    long long fpow(long long x, int y){
    	long long res = 1;
    	while(y){
    		if(y & 1) res = (res * x) % MOD;
    		x = (x * x) % MOD;
    		y >>= 1;
    	}
	    return res;
    } 

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

    const int N = 1e6 + 10;
    int rev[N], bit, tot;
    long long a[N], b[N];
    int n, m;
    
    void ntt(long long a[], int inv) {
        for (int i = 0; i < tot; i ++ )
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        
        for (int mid = 1; mid < tot; mid <<= 1) {
            long long Unit = fpow((inv == 1) ? 3 : 332748118, 998244352 / (mid << 1));
            for (int i = 0; i < tot; i += mid * 2) {
                long long Temp = 1;
                for (int j = 0; j < mid; j++) {
                    long long x = a[i + j], y = (Temp * a[i + j + mid]) % MOD;
                    a[i + j] = (x + y) % MOD, a[i + j + mid] = (x - y + MOD) % MOD;
                    Temp = (Temp * Unit) % MOD;
                }
            }
        }
    }

    void solve(vector<long long>& v1, vector<long long>& v2) {
        n = v1.size() - 1;
        m = v2.size() - 1;
        tot = 0; bit = 0;
        while ((1 << bit) < n + m + 1) bit ++;
        tot = 1 << bit;
        for (int i = 0; i < tot; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        for(int i = 0; i < tot; i++) a[i] = 0, b[i] = 0;
        for(int i = 0; i <= n; i++) a[i] = v1[i];
        for(int i = 0; i <= m; i++) b[i] = v2[i];
        ntt(a, 1), ntt(b, 1);
        for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        ntt(a, -1); 
        long long len = modInverse(tot, MOD);
        for (int i = 0; i <= n + m; i ++ ) {
            cout << (a[i] * len) % MOD << " ";
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1);
    vector<long long> b(m + 1);
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i <= m; i++) {
        cin >> b[i];
    }
    NTT :: solve(a, b);
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
