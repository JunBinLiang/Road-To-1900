//https://www.lanqiao.cn/problems/20032/learning/?contest_id=222
#include <iostream>
#include <cstring>
#include <algorithm>
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
  long long n;
  cin >> n;

  //((x + 1) * (x + 1) - 1) - x ^ 2
  //2x 
  //each consecutive interval has 3 possible integers
  
  //1 2 3
  //4 6 8
  //9 12 15
  //16 20 24
  //25 30 35
  //36 42 48
  //49
  long long ans = 0;
  long long s = sqrt(n);

  if(s - 1 >= 1) {
    long long e = s - 1;
    long long add = (1ll + e) * e / 2;
    add %= MOD;
    long long start = ((e * (e + 1)) % MOD * ((2 * e) % MOD + 1)) % MOD;
    start *= modInverse(6, MOD);
    ans += start;
    ans %= MOD;
    ans += (start + add);
    ans %= MOD;
    ans += (start + add + add);
    ans %= MOD;
  }

  //last round
  long long t = s * s;
  while(t <= n) {
    ans += (t);
    ans %= MOD;
    t += s;
  }
  cout << ans << endl;
}

int main()
{
  // 请在此输入您的代码
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
