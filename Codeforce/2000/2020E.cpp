#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//10:57
const int MOD = 1e9 + 7;

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

long long dp[2100], cur[2100];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), p(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> p[i];

    for(int i = 0; i < 2100; i++) dp[i] = cur[i] = 0;
    
    int base = modInverse(10000, MOD);
    dp[0] = (10000ll) * base % MOD; //success rate
    for(int i = 1; i <= n; i++) {
        long long success = ((p[i] + 0ll) * base) % MOD;
        long long fail = ((10000ll - p[i]) * base) % MOD;

        for(int b = 0; b < 2100; b++) {
            int newb = b ^ a[i];
            if(dp[b] == 0) continue;
            cur[newb] += (success * dp[b]);
            cur[newb] %= MOD;
            cur[b] += (fail * dp[b]);
            cur[b] %= MOD;
        }

        for(int b = 0; b < 2100; b++) {
            dp[b] = cur[b];
            cur[b] = 0;
        }
    }

    long long ans = 0;
    for(int i = 0; i < 2100; i++) {
        int b = i * i;
        ans += ((b + 0ll) * dp[i]);
        ans %= MOD;
    }
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
