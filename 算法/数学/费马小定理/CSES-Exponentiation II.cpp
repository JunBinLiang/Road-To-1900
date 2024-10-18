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

const int MOD =  1e9 + 7;

long long fpow(long long x, int y, int mod){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}  

/*
a ^ (b ^ c)
使用费马小定理
*/

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int t = fpow(b, c, MOD - 1);
    cout << fpow(a, t, MOD) << endl;
}

int main(){
    int t = 1;
    cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
