//https://www.lanqiao.cn/problems/21071/learning/?contest_id=263
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

typedef long long int ll;
ll mod_mul(ll a, ll b, ll mod)
{
    ll res = 0;
    while (b)
    {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}
 
ll mod_pow(ll a, ll n, ll mod)
{
    ll res = 1;
    while (n)
    {
        if (n & 1)
            res = mod_mul(res, a, mod);
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}
 
// Miller-Rabin随机算法检测n是否为素数
bool Miller_Rabin(ll n)
{
    if (n == 2)
        return true;
    if (n < 2 || !(n & 1))
        return false;
    ll m = n - 1, k = 0;
    while (!(m & 1))
    {
        k++;
        m >>= 1;
    }
    for (int i = 1; i <= 20; i++)  // 20为Miller-Rabin测试的迭代次数
    {
        ll a = rand() % (n - 1) + 1;
        ll x = mod_pow(a, m, n);
        ll y;
        for (int j = 1; j <= k; j++)
        {
            y = mod_mul(x, x, n);
            //if(y != 1) return false; failed
            if (y == 1 && x != 1 && x != n - 1)
                return false;
            x = y;
        }
        if (y != 1)
            return false;
    }
    return true;
}

const int N = 70;
int dp[N][N];
int dfs(int cur, int pre) {
  if(cur == 0) {
    return 1;
  }
  if(dp[cur][pre] != -1) return dp[cur][pre];
  int ans = 0;
  for(int i = 1; i <= min(pre, cur); i++) {
    if(cur >= i) {
      ans += dfs(cur - i, i);
    }
  }
  //cout << cur << " " << pre <<"  " << ans << endl;
  return dp[cur][pre] = ans;
}

void cal() {
  memset(dp, -1, sizeof dp);
}


int main()
{
  // 请在此输入您的代码
  long long n;
  cin >> n;
  cal();
  vector<int> a;
  long long o = n;
  for(int i = 2; i <= min(n, 1000000 + 100ll); i++) {
    if(n < i) break;
    if(n % i != 0) continue;
    int cnt = 0;
    while(n % i == 0) {
      n /= i;
      cnt++;
    }
    a.push_back(cnt);
  }

  //bool is = Miller_Rabin(n); 
  //n >= 10 ^ 7
  int mul = 1;
  if(n > 1000000) {
    long long s = sqrt(n);
    if(s * s == n) mul = 2;
  }
  
  unsigned long long ans = 1;
  for(int x : a) {
    long long way = 0;
    for(int start = 1; start <= x; start++) {
      way += dfs(x - start, start);
    }
    ans *= way;
  }
  cout << ans * mul << endl;
  return 0;
}
