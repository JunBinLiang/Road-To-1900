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

const int INF = 1e6;
bool comp(pair<int, int>& p1, pair<int, int>& p2) {
    return p1.second < p2.second;
}
void solve() {
    int n, x;
    cin >> n >> x;
    if(n == 1) {
        if(x == 0) cout << -1 << endl;
        else cout << x << endl;
        return;
    }
    
    if(x == 0) {
        if(n % 2 == 0) cout << n << endl;
        else {
            cout << 4 + n - 1 << endl;
        }
        return;
    }    
    
    long long ans = 0;
    int cnt = 0;
    for(int i = 0; i < 31; i++) {
        if(x & (1 << i)) { // 1
            cnt++;
        } else { //0

        }
    }
    ans = x;

    if(cnt >= n) {
        cout << ans << endl;
        return;
    }
    cnt = n - cnt;
    if(cnt % 2 == 0) {
        cout << ans + cnt << endl;
        return;
    }
    
    if(cnt % 2 == 0) {
        cout << ans + cnt << endl;
        return;
    }

    if(x % 2 != 1) {
        ans += (cnt + 1);
    } else {
        ans += (cnt - 1);
        if(x == 1) {
            ans += 4;
        } else {
            ans += 2;
        }
    }
    cout << ans << endl;
}


int main() {
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
