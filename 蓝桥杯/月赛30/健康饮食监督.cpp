//https://www.lanqiao.cn/problems/20650/learning/?contest_id=258
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

const int MOD = 998244353;
const int N = 2e5 + 100;
ll fact[N];

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

void init() {
  fact[0] = 1;
  for(int i = 1; i < N; i++) {
    fact[i] = fact[i - 1] * i;
    fact[i] %= MOD;
  }
}

void solve() {
    int n;
    cin >> n;
    if(n % 2 == 0) {
      n -= 2;
      long long ans = C(n, n / 2);
      ans *= 2;
      ans %= MOD;
      cout << ans << endl;
    } else {
      long long ans = 0;
      n -= 1;
      ans += C(n, n / 2);
      ans %= MOD;
      long long w = C(n - 2, (n - 2) / 2);
      w *= 4;
      w %= MOD;
      w *= (n - 1);
      w %= MOD;
      ans += w;
      ans %= MOD;
      cout << ans << endl;
    }
}


int main() {
    init();
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
