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

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

const int MOD = 1e9 + 7;
const int N = 2e5 + 100;
long long p1[N], p2[N];
long long f[N];

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

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll cnr(int n,int m) {
  return f[n] * fpow(f[n - m], MOD - 2) % MOD * fpow(f[m], MOD - 2) % MOD;
}

long long get(long long p[N], int l, int r) {
    if(l > r) return 1;
    if(l == 0) return p[r];
    return (p[r] * modInverse(p[l - 1], MOD)) % MOD;
}

void solve() {
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> R(n), C(m);
    vector<pair<int, int>> a, b;

    for(int i = 0; i < n; i++) {
        cin >> R[i];
        a.push_back({R[i], i});
    }
    for(int i = 0; i < m; i++) {
        cin >> C[i];
        b.push_back({C[i], i});
    }

    f[0] = 1;
    for(int i = 1; i <= n + m; i++) {
        f[i] = (f[i - 1] * i) % MOD;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> pr(n), pc(m);
    vector<int> c, d;

    for(int i = 0; i < n; i++) {
        int j = i;
        int cnt = 0;
        while(j < n && a[i].first == a[j].first) {
            pr[a[j].second] = c.size();
            cnt++;
            j++;
        }
        c.push_back(cnt);
        i = j - 1;
    }

    for(int i = 0; i < m; i++) {
        int j = i;
        int cnt = 0;
        while(j < m && b[i].first == b[j].first) {
            pc[b[j].second] = d.size();
            cnt++;
            j++;
        }
        d.push_back(cnt);
        i = j - 1;
    }

    for(int i = 0; i < c.size(); i++) {
        p1[i] = c[i];
        if(i) p1[i] *= p1[i - 1];
        p1[i] %= MOD; 
    }

    for(int i = 0; i < d.size(); i++) {
        p2[i] = d[i];
        if(i) p2[i] *= p2[i - 1];
        p2[i] %= MOD; 
    }

    while(t--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        
        if(R[r2] == R[r1] && C[c2] == C[c1]) {
          if(r1 == r2 && c1 == c2) {
            cout << 1 << endl;
            continue;
          }
          cout << 0 << endl;
          continue;
        }

        if(R[r2] < R[r1] || C[c2] < C[c1]) {
            cout << 0 << endl;
            continue;
        }

        if(R[r2] == R[r1] && r1 != r2 ) {
          cout << 0 << endl;
          continue;
        }

        if(C[c2] == C[c1] && c1 != c2 ) {
          cout << 0 << endl;
          continue;
        }
    
        long long ans = 1;
        if(r1 != r2) {
          ans *= get(p1, pr[r1] + 1, pr[r2] - 1);
          ans %= MOD;
        }
        if(c1 != c2) {
          ans *= get(p2, pc[c1] + 1, pc[c2] - 1);
          ans %= MOD;
        }
        int rcnt = pr[r2] - pr[r1];
        int ccnt = pc[c2] - pc[c1];
        ans *= cnr(rcnt + ccnt, rcnt);
        ans %= MOD;
        cout << ans << endl;
    }
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
