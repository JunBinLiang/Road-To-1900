#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;
//4:13
const int MOD = 998244353;
const int N = 4e5 + 10;

bool isp[N];
vector<int> pri;
void init() {
    memset(isp, 0, sizeof isp);
    for(int i = 2; i < N; i++) {
        if(isp[i]) continue;
        pri.push_back(i);
        for(int j = i; j < N; j += i) {
            isp[j] = true;
        }
    }
    //cout << pri.size() << endl;
}

void solve() {
    long long n, m;
    cin >> n >> m;
    //At least 2 sequence
    //1. [1 1 1 1 ...] is always a sequence
    //2. Find another sequence

    long long ans = 0;
    long long p = 1;
    for(int i = 1; i <= n; i++) {
        p *= (m % MOD);
        p %= MOD;
        ans += p;
        ans %= MOD;
    }

    int j = 0;
    p = 1;
    long long sub = 1;
    for(int i = 1; i <= n; i++) {
        while(j < pri.size() && pri[j] <= i) {
            p *= pri[j];
            p = min(p, m + 1);
            j++;
        }
        //divisible by all
        long long all = m / p;
        sub *= ((all) % MOD);
        sub %= MOD;
        ans -= sub;
        if(ans < 0) ans += MOD;   
    }
    cout << ans << endl;
}   

int main() {
    int t = 1;
    //std :: cin >> t;
    init();
    while(t--) {
        solve();
    }
    return 0;
}
