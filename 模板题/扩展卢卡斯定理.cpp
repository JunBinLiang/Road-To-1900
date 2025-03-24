//https://www.lanqiao.cn/problems/1160/learning/?page=2&first_category_id=1&second_category_id=8
//证明1 https://www.luogu.com.cn/article/tylybzfh
//证明2 https://www.luogu.com.cn/article/dz9piard
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

#define int long long
#define DEBUG puts ("emmmm")

const int maxn = 1e5 + 50, INF = 0x3f3f3f3f;

using namespace std;

inline int read () {
	register int x = 0, w = 1;
	char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

int n, m, p, tot;
int b[maxn], c[maxn], d[maxn];

inline int qpow (register int a, register int b, register int mod) {
	register int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

inline int ExGCD (register int a, register int b, register int &x, register int &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	register int d = ExGCD (b, a % b, x, y);
	register int tmp = x;
	x = y;
	y = tmp - (a / b) * y;
	return d;
}

inline int Inv (register int a, register int mod) { // 利用扩展欧几里德求逆元
	register int x = 0, y = 0;
	ExGCD (a, mod, x, y);
	return (x % mod + mod) % mod;
}

inline int Calc (register int n, register int p, register int pk) {
	if (n == 0) return 1;
	register int ans = 1;
	for (register int i = 1; i <= pk; i ++) { // 每个循环节
		if (i % p) ans = ans * i % pk;
	}
	ans = qpow (ans, n / pk, pk); // 计算所有的循环节
	for (register int i = 1; i <= n % pk; i ++) { // 乘下剩下的
		if (i % p) ans = ans * i % pk;
	}
	return ans * Calc (n / p, p, pk) % pk;
}

inline int C (register int n, register int m, register int p, register int pk) {
	if (n == 0 || m == 0 || n == m) return 1;
	if (n < m) return 0;
	register int nn = Calc (n, p, pk), mm = Calc (m, p, pk), nm = Calc (n - m, p, pk), cnt = 0, k = n - m;
	while (n) n /= p, cnt += n;
	while (m) m /= p, cnt -= m;
	while (k) k /= p, cnt -= k;
	return nn * Inv (mm, pk) % pk * Inv (nm, pk) % pk * qpow (p, cnt, pk) % pk;
}

inline int CRT () { // 中国剩余定理
	register int M = 1, ans = 0;
	for (register int i = 1; i <= tot; i ++) {
		M *= c[i];
	}
	for (register int i = 1; i <= tot; i ++) {
		d[i] = Inv (M / c[i], c[i]);
	}
	for (register int i = 1; i <= tot; i ++) {
		ans += b[i] * (M / c[i])  * d[i];
	}
	return (ans % M + M) % M;
}

inline void ExLucas (register int n, register int m, register int p) {
	register int tmp = sqrt (p);
	for (register int i = 2; i <= tmp && p >= 1; i ++) { // 将p拆分质因数
		register int pk = 1;
		while (p % i == 0) p /= i, pk *= i;
		if (pk > 1) {
			b[++ tot] = C (n, m, i, pk), c[tot] = pk;
		}
	}
	if (p > 1) b[++ tot] = C (n, m, p, p), c[tot] = p;
	printf ("%lld\n", CRT ());		
}

signed main () {
	n = read(), m = read(), p = read();
	ExLucas (n, m, p);	
	return 0;
}
