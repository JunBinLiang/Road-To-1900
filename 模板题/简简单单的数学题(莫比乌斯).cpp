//https://www.lanqiao.cn/problems/4341/learning/
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

int primes[N], cnt, mu[N], sum[N];
bool st[N];

void init() {
    memset(st, 0, sizeof st);
    mu[1] = 1;
    for (int i = 2; i < N; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i, mu[i] = -1;
        for (int j = 0; primes[j] * i < N; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
            mu[primes[j] * i] = -mu[i];
        }
    }
    for (int i = 1; i < N; i ++ ) sum[i] = sum[i - 1] + mu[i];
}

//a*  b * c * gcd(a, b, c)
long long dp2[N], dp3[N];
const int MOD = 998244353;
void init1(int n) {
    memset(dp2, 0, sizeof dp2);
    memset(dp3, 0, sizeof dp3);
    dp2[1] = 1;
    dp3[1] = 1; 
    for(int i = 2; i <= n; i++) {
        long long sum = (i - 1ll) * i / 2;
        sum %= MOD;

        long long ii = (i + 0ll) * i;
        ii %= MOD;
        long long iii = ii * i;
        iii %= MOD;

        dp2[i] = dp2[i - 1] + (sum * i) * 2; 
        dp2[i] %= MOD;
        dp2[i] += ((i + 0ll) * i);
        dp2[i] %= MOD;
        dp3[i] = dp3[i - 1];
        dp3[i] += (dp2[i - 1] * i * 3); //place one i
        dp3[i] %= MOD;
        dp3[i] += (ii * sum * 3); //place two i
        dp3[i] %= MOD;
        dp3[i] += (iii);
        dp3[i] %= MOD;
    }
    
    //for(int i = 1; i <= 3; i++) cout << dp2[i] << " ";
    //cout << endl;
    //for(int i = 1; i <= 3; i++) cout << dp3[i] << " ";
    //cout << endl;
}

long long F(int n) {
    return dp3[n];
}

long long f(int n, int g) {
    long long s = 0;
    for(int d = g; d <= n; d += g) {
        long long dd = (d + 0ll) * d;
        dd %= MOD;
        long long ddd = dd * d;
        ddd %= MOD;
        s += ((mu[d / g] + 0ll) * F(n / d) * (ddd));
        s %= MOD;
        if(s < 0) s += MOD;
    }
    return s;
}

void test() {
    for(int n = 1; n <= 3; n++) {
        long long s = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                s += i * j;
            }
        }
        cout << n << ":  " << s << endl;
    }
    cout << endl;
    for(int n = 1; n <= 3; n++) {
        long long s = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                for(int k = 1; k <= n; k++) {
                    s += (i * j * k);
                }
            }
        }
        cout << n << ":  " << s << endl;
    }
}

void solve() {
    int n;
    cin >> n;
    init1(n);
    //test();
    long long ans = 0;
    for(int g = 1; g <= n; g++) {
        ans += ((g + 0ll) * f(n, g));
        ans %= MOD;
    }
    cout << ans << endl;
    
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  init();
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
