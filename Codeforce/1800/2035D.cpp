#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <string.h>


using namespace std;  

//5:19 - 5:49
const int MOD = 1e9 + 7;

long long fpow(long long x, int y){
    long long res = 1;
    while(y){
    	if(y & 1) res = (res * x) % MOD;
    	x = (x * x) % MOD;
    	y >>= 1;
    }
	return res;
} 

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long s = 0;
    vector<pair<int, int>> stk;
    for(int i = 0; i < n; i++) {
        int v = a[i];
        int cnt = 0;
        while(v % 2 == 0) {
            v /= 2;
            cnt++;
        }
        long long cur = a[i];
        while(stk.size() > 0 && cur > stk.back().first) {
            pair<int, int> p = stk.back(); stk.pop_back();
            cnt += p.second;
            cur = min(100000000000000ll, cur * 1 << (min(30, p.second)));
            s -= (((p.first + 0ll) * fpow(2, p.second)) % MOD);
            if(s < 0) s += MOD;
            s += p.first;
            s %= MOD;
        }
        
        s += ((v * fpow(2, cnt)) % MOD);
        s %= MOD;
        stk.push_back({v, cnt});
        cout << s << " ";
    }
    cout << endl;
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
