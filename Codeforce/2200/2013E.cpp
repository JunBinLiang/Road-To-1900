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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int g = a[0];
    for(int i = 0; i < n; i++) g = __gcd(g, a[i]);
    sort(a.begin(), a.end());

    int t = 1;
    int x = a[0];
    long long ans = x;
    while(x != g) {
        t++;
        int mn = x;
        for(int i = 0; i < n; i++) {
            int gc = __gcd(x, a[i]);
            mn = min(mn, gc);
        }
        ans += mn;
        x = mn;
    }

    cout << ans + ((g + 0ll) * (n - t)) << endl;
    
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
