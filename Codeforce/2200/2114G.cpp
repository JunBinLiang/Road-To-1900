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

int f(int n) {
    if(n == 0) return 0;
    int x = 0;
    while(n % 2 == 0) {
        n /= 2;
        x++;
    }
    return 1 << x;
}

int cal(int x, int y) {
    if(x % y != 0) {
        return f(x);
    }
    int oldx = x;
    int cnt = 0;
    while(x % 2 == 0) {
        x /= 2;
        cnt++;
        if(x == y) {
            return f(oldx) - f(x * 2) + 1;
        }
    }
    return 1 << cnt;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> pref(n), suff(n);
    
    for(int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + cal(a[i - 1], a[i]);
        //cout << i << "  " << pref[i] << endl;
    }
    //cout << endl;

    for(int i = n - 2; i >= 0; i--) {
        suff[i] = suff[i + 1] + cal(a[i + 1], a[i]);
        //cout << i << "  " << suff[i] << endl;
    }
    
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans = max(ans, pref[i] + suff[i] + f(a[i]));
    }

    if(ans >= k) cout << "YES" << endl;
    else cout << "NO" << endl;
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

/*
4
4 6
10 5 3 6
5 6
5 1 3 6 3 
3 8
4 2 4
4 7
5 6 1 10
*/
