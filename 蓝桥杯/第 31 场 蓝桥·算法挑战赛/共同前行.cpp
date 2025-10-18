//https://www.lanqiao.cn/problems/21069/learning/?contest_id=263
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
  if(n == 1) {
    cout << 2 << endl;
    return;
  }
  if(n == 2) {
    cout << 6 << endl;
    return;
  }
  n -= 2;
  cout << (6 * fpow(3, n) ) % MOD << endl;

}

int main()
{
  // 请在此输入您的代码
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
