#include <iostream>
#include <cstring>
#include <algorithm>
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
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> r(n);
    long long s = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] < 0) s += abs(a[i]);
        r[i] = s;
    }

    long long ans = 0;
    s = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < 0) {
            ans = max(ans, s + r[i]);
        } else {
            s += a[i];
            ans = max(ans, s);
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
