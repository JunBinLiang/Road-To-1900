// Problem: D. Small GCD
// Contest: Codeforces - Codeforces Round 911 (Div. 2)
// URL: https://codeforces.com/contest/1900/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))
 
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;
 
const int maxn = 100100;
const int N = 100000;
 
ll n, a[maxn], b[maxn], c[maxn], f[maxn];
 
void solve() {
	mems(b, 0);
	mems(f, 0);
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		++b[a[i]];
	}
	for (int i = 1; i <= N; ++i) {
		c[i] = c[i - 1] + b[i];
	}
	for (int i = 1; i <= N; ++i) {
		ll s = 0;
		for (int j = i; j <= N; j += i) {
			f[i] += s * b[j] * (c[N] - c[j]) + s * (b[j] * (b[j] - 1) / 2) + b[j] * (b[j] - 1) / 2 * (c[N] - c[j]) + b[j] * (b[j] - 1) * (b[j] - 2) / 6;
			s += b[j];
		}
	}
	ll ans = 0;
	for (int i = N; i; --i) {
		for (int j = i + i; j <= N; j += i) {
			f[i] -= f[j];
		}
		ans += f[i] * i;
	}
	printf("%lld\n", ans);
}
 
int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
