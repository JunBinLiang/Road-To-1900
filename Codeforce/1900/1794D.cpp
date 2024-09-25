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
using ll = long long;
//6:15 - 7:10

const int MOD = 998244353;
const int N = 1e6 + 10;
bool vis[N], isp[N];
long long fact[N];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  
  

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
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

int C[2023][2023];
void init() {
    memset(vis, 0, sizeof vis);
    memset(isp, 0, sizeof isp);
    for(int i = 2; i < N; i++) {
        if(vis[i]) continue;
        isp[i] = true;
        for(int j = i; j < N; j += i) vis[j] = true;
    }
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i ) % MOD;
    }
    
    C[0][0] = 1;
    for(int i = 1;i <= 2022; i++) {
      C[i][0]=1;
      for(int j = 1;j <= i;j++) {
        C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
      }
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    n = 2 * n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> pri, nonpri;
    map<int, int> f;
    for(int i = 0; i < n; i++) {
        if(isp[a[i]]) pri.push_back(a[i]);
        else nonpri.push_back(a[i]);
        f[a[i]]++;
    }
    

    int uni = 0;
    for(auto it = f.begin(); it != f.end(); it++) {
        int v = it -> first;
        if(isp[v]) {
            uni++;
        }
    }
  
    if(uni < n / 2) {
        cout << 0 << endl;
        return;
    }
    
    long long nonpriway = C[n / 2][nonpri.size()];
    nonpriway *= fact[nonpri.size()];
    nonpriway %= MOD;
    for(auto it = f.begin(); it != f.end(); it++) {
        int v = it -> first, cnt = it -> second;
        if(!isp[v]) {
            nonpriway *= modInverse(fact[cnt], MOD);
            nonpriway %= MOD;
        }
    }
    
    vector<int> dp(pri.size() - (n / 2) + 1);
    dp[0] = 1;
    vector<int > cur(dp.size());
    for(auto it = f.begin(); it != f.end(); it++) {
        int v = it -> first, cnt = it -> second;
        if(!isp[v]) continue;
        for(int j = 0; j < dp.size(); j++) {
            cur[j] = 0;
            if(j >= (cnt - 1)) {
                int w = C[j][cnt - 1];
                cur[j] += (((w + 0ll) * dp[j - (cnt - 1)]) % MOD);
                cur[j] %= MOD;
            }
            
            if(j >= (cnt)) {
                int w = C[j][cnt];
                cur[j] += (((w + 0ll) * dp[j - (cnt)]) % MOD);
                cur[j] %= MOD;
            }
        }
        for(int j = 0; j < dp.size(); j++) {
            dp[j] = cur[j];
        }
    }

    long long ans = dp[pri.size() - n / 2] * nonpriway;
    ans %= MOD;
    cout << ans << endl;
}   

int main() {
    int t = 1;
    init();
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
