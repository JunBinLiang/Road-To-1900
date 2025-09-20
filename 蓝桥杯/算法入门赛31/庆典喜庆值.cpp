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
const int MOD = 998244353;

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        long long q = a / m;
        long long t = m;
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

void solve() {
  int n;
  cin >> n;
  long long ans = 0;
  long long x = n;
  long long y = (1ll + n) * n / 2;
  y %= MOD;
  y *= 3;
  y %= MOD;

  long long m = modInverse(6, MOD);
  long long z = 0;
  z = (n + 0ll) * (n + 1);
  z %= MOD;
  z *= m;
  z %= MOD;
  z *= (2 * n + 1);
  z %= MOD;
  z *= 3;
  z %= MOD;

  ans += x;
  ans %= MOD;
  ans += y;
  ans %= MOD;
  ans += z;
  ans %= MOD;
  cout << ans << endl;
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
