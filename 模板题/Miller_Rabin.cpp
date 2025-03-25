#include <iostream>
using namespace std;
//https://blog.csdn.net/ECNU_LZJ/article/details/72675595
//判断大素数

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

void solve() {
  long long n;
  cin >> n;
  if(n == 1) {
    cout << 0 << endl;
    return;
  }

  if(Miller_Rabin(n)) cout << 1 << endl;
  else cout << 0 << endl;

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
