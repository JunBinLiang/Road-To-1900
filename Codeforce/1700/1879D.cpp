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


//5:19
const int MOD = 998244353;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    vector<int> prefix(n + 1);
    int xo = 0;
    for(int i = 0; i <= n; i++) {
        xo ^= a[i];
        prefix[i] = xo;
    }
    
    for(int i : prefix) cout << i << " ";
    cout << endl;

    long long ans = 0;
    vector<long long> v0(32);
    vector<long long> v1(32);
    vector<long long> s0(32);
    vector<long long> s1(32);
    for(int i = 0; i <= n; i++) {
        if(i) {
            for(int j = 0; j < 31; j++) {
                long long val = (1 << j);
                if(prefix[i] & (1 << j)) { //1
                    long long s =  (v0[j] * i - s0[j]);
                    s %= MOD;
                    s *= val;
                    s %= MOD;
                    ans += val;
                    ans %= MOD;
                } else { //zero
                    long long s = (v1[j] * i - s1[j]);
                    s %= MOD;
                    s *= val;
                    s %= MOD;
                    ans += val;
                    ans %= MOD;
                }
                    ans %= MOD;
            }
        }
        
        
        for(int j = 0; j < 31; j++) {
            if(prefix[i] & (1 << j)) {
                v1[j]++;
                s1[j] += i;
            } else {
                v0[j]++;
                s0[j] += i;
            }
        }
    }

    cout << ans << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
