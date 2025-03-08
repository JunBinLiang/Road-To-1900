//https://www.lanqiao.cn/problems/20265/learning/?contest_id=249
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
const ll INF = 1e18;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long o = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        o |= a[i];
    }
    long long ans = 0;
    for(int i = 0; i < 60; i++) {
        if((o & (1 << i)) == 0) {
            ans = (1ll << i);
            break;
        }
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
