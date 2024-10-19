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

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
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

//5:38 - 5:51
const int MOD = 998244353;
void solve() {
    string s;
    cin >> s;
    vector<int> a;
    for(int i = 0; i < s.size(); i++) {
        int j = i;
        int cnt = 0;
        while(j < s.size() && s[i] == s[j]) {
            j++;
            cnt++;
        }
        a.push_back(cnt);
        i = j - 1;
    }

    vector<long long> f(s.size() + 1);
    f[0] = 1;
    for(int i = 1; i < f.size(); i++) {
        f[i] = f[i - 1] * i;
        f[i] %= MOD;
    }

    int sum = 0;
    long long w = 1;
    for(int i = 0; i < a.size(); i++) {
        sum += (a[i] - 1);
        w *= f[a[i]];
        w %= MOD;
    }
    w *= f[sum];
    w %= MOD;
    for(int i = 0; i < a.size(); i++) {
        w *= modInverse(f[a[i] - 1], MOD);
        w %= MOD;
    }
    cout << sum << " " << w << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
