//https://www.lanqiao.cn/problems/20314/learning/?contest_id=254
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt(3010);
    for(int x : a) cnt[x]++;
    long long ans = 1;
    for(int i = 1; i <= 3000; i++) {
        if(cnt[i] == 0) continue;
        for(int j = i + 1; j <= 3000; j++) {
            if(cnt[j] == 0) continue;
            int xo = i ^ j;
            ans *= xo;
            ans %= MOD;
        }
    }

    for(int i = 1; i <= 3000; i++) {
        if(cnt[i] > 1) {
            cout << 0 << endl;
            return;
        }
    }
    
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
