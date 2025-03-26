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


const int N = 1e5 + 10;

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

long long F(int n, int k) {
    long long d = n / k;
    return d * d;
}

long long cal(int n, int k) {
    long long s = 0;
    for(int d = k; d <= n; d += k) {
        s += (F(n, d) * mu[d / k]);
    }
    //cout << n << "  " << k << "  " << s << endl;
    return s;
}

void solve() {
    int n;
    cin >> n;
    init();
    long long ans = 0;
    for(int g = 1; g <= n; g++) {
        ans += (cal(n, g) * g);
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
