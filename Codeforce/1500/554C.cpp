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
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

//9:16 - 9:26
const int MOD = 1e9 + 7;
const int N = 1e6 + 10;
long long fact[N];

long long fpow(long long  x, int y){
	long long  res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

long long C(int n,int m) {
    return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long ans = 1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int cnt = a[0];
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    for(int i = 1; i < n; i++) {
        //put cnt balls on to 
        ans *= C(a[i] + cnt - 1, cnt);
        ans %= MOD;
        cnt += a[i];
    }

    cout << ans << endl;
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
