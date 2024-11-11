#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  

map<pair<long long, long long>, long long> dp;
long long dfs(long long n, long long start, long long M) { //[0 : n]
    if(n == 0) {
        return 0;
    }

    if(dp.find({n, start}) != dp.end()) {
        return dp[{n, start}];
    }

    int bit = -1;
    for(int i = 0; i < 61; i++) {
        if(n & (1ll << i)) {
            bit = i;
        }
    }   

    long long ans = 0, xo = 0;
    long long t = (n) - (1ll << bit); //11 - 8 = 3 [0 1 2 3]
    if(start > n) {
        if((t + 1) % 2 == 1) {
            xo = (1ll << bit);
        }
        ans = xo ^ dfs(t, start, M) ^ dfs((1ll << bit) - 1, start, M);
    } else {
        long long L = (1ll << bit), R = n;
        long long x = (L - start) / M;
        long long first = start + (M * x);
        if(first < L) {
            first += M;
        }
        
        //cout << L << "  " << R << "  " << start << "  " << x << "  " << first <<"  " << endl;

        if(first <= R) {
            long long cnt = (R - first) / M + 1;
            if((t + 1 - cnt) % 2 == 1) {
                xo = (1ll << bit);
            }
            ans = xo ^ dfs((1ll << bit) - 1, start, M) ^ dfs(t, first - (1ll << bit), M);
        } else {
            if((t + 1) % 2 == 1) {
                xo = (1ll << bit);
            }
            ans = xo ^ dfs((1ll << bit) - 1, start, M) ^ dfs(t, first - (1ll << bit), M);
        }
    }
    return dp[{n, start}] = ans;
}

long long get(long long n, int i, long long k) {
    if(n == 0) {
        return 0;
    }
    //dp.clear();
    return dfs(n, k, (1ll << i));
}

void solve() {
    long long L, R, i, k;
    cin >> L >> R >> i >> k;
    dp.clear();
    long long x = get(L - 1, i, k); 
    long long y = get(R, i, k);
    cout << (x ^ y) << endl;
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
