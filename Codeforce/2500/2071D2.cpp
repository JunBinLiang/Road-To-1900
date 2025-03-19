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

const int N = 2e5 + 10;
vector<int> a, b, p;
vector<int> ps, even;
map<long long, long long> dp1, dp2;
int n;

int getx(vector<int>& p, int l, int r) {
	return p[r] ^ p[l - 1];
}

int get(vector<int>& p, int l, int r) {
	return p[r] - p[l - 1];
}

long long recal1(long long m);
long long recal2(long long m);

long long recal1(long long m) { //[n : m] take all
	if(dp1.find(m) != dp1.end()) return dp1[m];
	long long c1 = 0, c2 = 0;
	int P = p[n];
	if(m >= (2 * n)) {
    	c1 = ((m - 2 * n) / 4 + 1);
	}
	if(m >= (2 * n + 1)) {
    	c2 = ((m - 2 * n - 1) / 4 + 1);
	}
	c1 *= P;
	c2 *= P;
	long long s = get(ps, n, min(2 * n - 1ll, m));
    
	//cout << "recal1be " << m << "  |" << c1 << " " << c2 <<"  " << s << endl;
	int t = 4 * n;
	for(int i = 2 * n + 2; i <= min(4 * n - 1ll, m); i += 4) {
    	c1 += (P ^ b[i / 2]);
    	if(i + 1 <= m) {
        	c2 += (P ^ b[i / 2]);
    	}
	}

	long long o = m, e = m;
	if(m % 2 == 1) e--;
	else o--;
	if(e >= t) {
    	c1 += recal2(e / 4);
	}
	if(o >= t) {
    	c2 += recal2(o / 4);
	}
	//cout << "recal1 " << m << "  |" << c1 << " " << c2 <<"  " << s << endl;
	return dp1[m] = c1 + c2 + s;
}

long long recal2(long long m) { //[n : m] take half
	if(dp2.find(m) != dp2.end()) {
    	return dp2[m];
	}

	//take even but not odd
	long long s = 0;
	int P = p[n];
	for(int i = n; i <= min(m, 2 * n + 0ll - 1); i++) {
    	if(i % 2 == 0) {
        	s += b[i];
    	}
	}
    
	long long c1 = 0, c2 = 0;
	if(m >= (2 * n)) {
    	c1 = ((m - 2 * n) / 4 + 1);
	}
	c1 *= P;

	int j = n + 1;
	int t = 4 * n;
	for(int i = 2 * n + 2; i <= min(4 * n - 1ll, m); i += 4) {
    	c1 += (P ^ b[i / 2]);
	}

	long long o = m, e = m;
	if(m % 2 == 1) e--;
	else o--;

	if(e >= t) {
    	s += recal2(e / 4);
	}
	/*
	if(o >= t) {
    	s += recal1(o / 4);
	}*/
	//cout << "recal2 " << m << "   " << s << "  " << c1 << endl;
	return dp2[m] = s + c1;
}

long long cal(long long m) {
	if(m < n) {
    	return ps[m];
	}
	return recal1(m) + ps[n - 1];
}

void solve() {
	long long L, R;
	cin >> n >> L >> R;
	a = vector<int>(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	if(n % 2 == 0) {
    	n++;
    	int xo = 0;
    	for(int i = 1; i <= n / 2; i++) {
        	xo ^= a[i];
    	}
    	a.push_back(xo);
	}

	if(n == 1) {
    	a.push_back(a[1]);
    	a.push_back(a[1]);
    	n = 3;
	}

	p = vector<int> (2 * n + 1);
	for(int i = 1; i <= n; i++) {
    	p[i] = a[i];
    	if(i > 1) p[i] ^= p[i - 1];
	}

	b = vector<int>(2 * n + 1);
	for(int i = 1; i <= n; i++) b[i] = a[i];
	for(int i = n + 1; i < b.size(); i++) {
    	b[i] = getx(p, 1, i / 2);
    	p[i] = b[i];
    	p[i] ^= p[i - 1];
	}
    

	ps = vector<int>(2 * n + 1);
	even = vector<int>(2 * n + 1);
	int es = 0;
	for(int i = 1; i <= 2 * n; i++) {
    	ps[i] = b[i];
    	if(i) ps[i] += ps[i - 1];
    	if(i % 2 == 0) {
        	es += b[i];
    	}
    	even[i] = es;
	}
    
	dp1.clear();
	dp2.clear();

	/*for(int x : b) cout << x << " ";
	cout << endl;
	for(int x : ps) cout << x << " ";
	cout << endl << endl;*/
	
	long long s1 = cal(R);
	//cout << endl;
	long long s2 = cal(L - 1);
    
	//cout << s1 << "  " << s2 << "   |" << s1 - s2 << endl;
	cout << s1 - s2 << endl;
    
	/*cout << endl << endl;
    for(int i = 1; i <= 2 * n; i++) cout << b[i] << " ";

	for(int j = 2 * n + 1; j <= 69; j++) {
    	int o = 0;
    	for(int i = 1; i <= j / 2; i++) {
        	o ^= b[i];
    	}
    	b.push_back(o);
	}
	
	for(int i = 1; i <= 15; i++) cout << b[i] << " ";
	cout << endl;
	
	/*int cnt = 0;
	for(int i = 1; i <= b.size(); i++) if(b[i]) cnt++;
	cout << cnt << endl;
	
	cout << endl;
	int x = 0;
	for(int i = 1; i <= 64; i++) x += b[i];
	cout << x << endl;
	x = 0;
	for(int i = 1; i <= 69; i++) x += b[i];
	cout << x << endl;*/
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
	solve();
  }
  return 0;
}


/*
[we have a1 - a25] if n = 13


a26 a27 = p
a28 a29 = p a14
a30 a31 = p
a32 a33 = p a16
a34 a35 = p
a36 a37 = p a18
a38 a39 = p
a40 a41 = p a20
a42 a43 = p
a44 a45 = p a22
a46 a47 = p
a48 a49 = p a24
a50 a51 = p

a52 a53 = p a26
a54 a55 = p
a56 a57 = p a28
a58 a59 = p
a60 a61 = p a30
a62 a63 = p
a64 a65 = p a32
a66 a67 = p
a68 a69 = p a34


______________________

a1 = 1
a2 = 1
a3 = 1
a4 = 0
a5 = 0
a6 = 1 = p



a6 a7 = p
a8 a9 = p a4 (x)
a10 11 = p

a12 13 = p a6
a14 15 = p
a16 17 = p a8
a18 19 = p
a20 21 = p a10
a22 a23 = p
a24 a25 = p a12 (x)
*/
