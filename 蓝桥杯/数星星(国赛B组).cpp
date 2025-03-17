//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P10912
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

const int MOD = 1000000007;
ll fact[100010];
ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
} 

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

vector<int> deg;
long long get(int k) {
    if(k <= 0) {
        return 0;
    }
    int n = deg.size();
    long long s = 0;
    if(k >= 1) s += n;
    if(k >= 2) s += (n - 1);

    for(int i = 0; i < n; i++) {
        int d = deg[i];
        //C(d, 2) + C(d, 3) + ... C(d, k - 1)
        for(int j = 2; j <= min(d, k - 1); j++) {
            s += C(d, j);
            s %= MOD;
        }
    }
    return s;
}

void solve() {
    int n;
    cin >> n;
    deg = vector<int>(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        deg[u]++;
        deg[v]++;
    }

    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    int L, R;
    cin >> L >> R;
    long long ans = get(R) - get(L - 1);
    if(ans < 0) ans += MOD;
    cout << ans << endl;
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
